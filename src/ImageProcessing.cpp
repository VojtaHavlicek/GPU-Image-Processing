//---------------------------------------------------------------------
// 
// Imperial College London
//
// Project: Image Processing Using GPU 
//
// Author: Vojtech Havlicek, Daniel Greening
//
// The original code for GLUT initialization was adapted from 
// Pavel Tisnovsky's tutorial at Root.cz
// 
//---------------------------------------------------------------------

#include <GL/glew.h> // header file of GLEW;
#include <GL/glut.h> // header file of GLUT functions
#include <iostream>  // input/output stream for debug
#include <string>
#include <cmath>
#include "textfile/textfile.h"     // includes textfile manipulation utilities
#include "shaders/ShaderProgram.h" // includes the ShaderProgram Class
#include "ImageProcessing.h"       // includes interface for the file (function definitions). Always include as last !!!
#include "soil/SOIL.h" // Soil 

//
// Uses the standard namespace for io operations
//
using namespace std;



void onKeyboard(unsigned char key, int x, int y)
{
	key=(key>'A' && key<='Z') ? key+'a'-'A':key; 
    switch (key) {
		
		//--- EXIT CASES
        case 'x':                 
        case 'q':
        case 27:          
            exit(0);
        break;
        
		//----------------------------------
		case 'f': 
			if(!fullscreen){
				fullscreen = true;
				glutFullScreen();           
			}else{
				glutReshapeWindow(W, H);
				glutPositionWindow(200, 200);
				fullscreen = false;
			}

        break;
    }
}



int main(int argc, char **argv)
{
	
	
	cout << "Image Processing Using GPU \n\nCreated by Vojtech Havlicek & Daniel Greening (2012)\nSupervised by Lionel Fachkamps\nImperial College\n---\nOutput:\n";

	
	/**
	Prepares GLUT
	*/
    glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(W,H);
	glutInitWindowPosition(200,200);

	/**
	Create the new Window
	*/
    win1 = glutCreateWindow("Image Processing Project");
	cout << "OpenGL version: "<< glGetString(GL_VERSION) << "\n";  // Check for OpenGL version
	
	glutDisplayFunc(openGLDrawScene);      
	//glutIdleFunc(openGLDrawScene);
	glutKeyboardFunc(onKeyboard);
	glutReshapeFunc(changeSize);
	
	glClearColor(0.0,0.0,0.0,1.0);
	//glEnable(GL_CULL_FACE);

	//OpenGLInit();
	glewInit();

	if(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	{
		cout << "Shaders supported" << "\n";
	}

	/**
	Pre-run application entry point
	*/

	//prepareShaders();  //shaders disabled while trying out textures

	/**
	Starts the main GLUT loop
	*/
	glutMainLoop(); //starts the main loop of the app.

    return 0;             
}


/**
Initialization function for openGL. Setups the OpenGL in the beginning.
Check if it does not collide with GLUT initialization.
*/

int openGLInit(GLvoid)
{
	
	return 0;
}


/**
Entry point for shader program production
*/
//--- handlers to shaders

ShaderProgram shaderProgram;

void prepareShaders()
{
	/**
	Test for ShaderProgram Class
	*/
	
	shaderProgram = ShaderProgram();
	shaderProgram.addFragmentShaderSource("src/shaders/monoColorTest/testFragmentShader.frag");
	shaderProgram.addVertexShaderSource("src/shaders/monoColorTest/testVertexShader.vert");
	
	shaderProgram.prepareProgram();
	shaderProgram.run();
}

//-----------------------------------------------------------------------------------------
//
//	An entry point function for all OpenGL drawing. Called at onDisplay.
//
GLuint textureHandler; //I think this needs to be GLuint instead of unsigned int
GLint colorLoc; //Location of colorVec
float red=0.5;
bool colorForward=true;

void openGLDrawScene() 
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	//colorLoc = glGetUniformLocation(shaderProgram.program, "colorVec"); //gets location of colorVec
	//glUniform4f(colorLoc, sin(red), 0.0f, 1.0f, 1.0f); //modifies colorVec

	/*
	if(colorForward==true){ 
		red+=0.0001f;
		if(red>0.99f){
			colorForward = false;
		}
	}
	else{
		red-=0.0001f;
		if(red<0.01f){
			colorForward = true;
		}
	}
	*/
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //prevents image from bleeding over to other side
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //same but for in other axis
	
	textureHandler = SOIL_load_OGL_texture("src/artwork.png",
							SOIL_LOAD_AUTO,
							SOIL_CREATE_NEW_ID,
							SOIL_FLAG_INVERT_Y);

	cout << "textureHandler "<< textureHandler << "\n";
	
	glBindTexture(GL_TEXTURE_2D, textureHandler);   


	glTranslated(-1.0,-1.0,0.0);
	glBegin(GL_QUADS);
		//glColor3d(1.0,1.0,1.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2d(0.0,0.0);

		//glColor3d(1.0,0.0,1.0);
		glTexCoord2f(1.0f, 0.0f); // TexCoords are normalized, in range [0,1]
		glVertex2d(2.0,0.0);

		//glColor3d(1.0,1.0,0.0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2d(2.0,2.0);
		
		//glColor3d(0.0,1.0,1.0);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2d(0.0,2.0);
	glEnd();



	glutSwapBuffers();
}

void changeSize(int w, int h) {


	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	
	
}