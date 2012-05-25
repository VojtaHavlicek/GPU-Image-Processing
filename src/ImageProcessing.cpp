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
#include "shaders/Shaders.h"       // includes the ShaderProgram Class
#include "ImageProcessing.h"       // includes interface for the file (function definitions). Always include as last !!!
#include "soil/SOIL.h"             // Soil 

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
    win1 = glutCreateWindow("Image Processing Project");
	
	cout << "OpenGL version: "<< glGetString(GL_VERSION) << "\n";  // Check for OpenGL version
	
	glutDisplayFunc(openGLDrawScene);      
	glutIdleFunc(openGLDrawScene);
	glutKeyboardFunc(onKeyboard);
	glutReshapeFunc(changeSize);
	
	glClearColor(0.0,0.0,0.0,1.0);
	
	glewInit();

	if(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		cout << "ARB extensions supported" << "\n";
	



	prepareTexture(); // prepares the texture to be displayed.
	prepareShaders();  //shaders disabled while trying out textures

	openGLInitScene();
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
	shaderProgram = EdgeDetectionShader();
	shaderProgram.prepareProgram();
}


/**
Prepares texture for later usage
*/
GLuint textureHandler;
void prepareTexture()
{
	glEnable(GL_TEXTURE_2D);
	
	glActiveTextureARB(GL_TEXTURE0);
	textureHandler = SOIL_load_OGL_texture("src/artwork.png",
							SOIL_LOAD_AUTO,
							SOIL_CREATE_NEW_ID,
							NULL);
	
	cout << "textureHandler trace: "<< textureHandler << "\n";
	
	
}

/**
Inits the whole scene. All stuff about setting of uniforms should be done here.
*/
GLint location; //Location of Alpha
GLint width;
GLint height;
GLint brightnessLevel;

void openGLInitScene()
{
    location = glGetUniformLocationARB(shaderProgram.program, "tex");
	glUniform1iARB(location, GL_TEXTURE0_ARB); 

	//passes dimension of the image to shader
	width = glGetUniformLocationARB(shaderProgram.program, "width");
	glUniform1fARB(width, (float) W);

	height = glGetUniformLocationARB(shaderProgram.program, "height");
	glUniform1fARB(width, (float) H);

	//--- Starts the program
	shaderProgram.run();
}

//-----------------------------------------------------------------------------------------
//
//	An entry point function for all OpenGL drawing. Called at onDisplay.
//
double a = 0;
void openGLDrawScene() 
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	glBindTexture(GL_TEXTURE_2D, textureHandler);
	
	brightnessLevel = glGetUniformLocationARB(shaderProgram.program, "time");
					  glUniform1fARB(brightnessLevel, (GLfloat)(a));
	a += 0.001;

	glBegin(GL_QUADS);
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 0.0f);
		glVertex2d(0.0,0.0);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 0.0f); // TexCoords are normalized, in range [0,1]
		glVertex2d(W,0.0);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 1.0);
		glVertex2d(W,H);
		
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 1.0);
		glVertex2d(0.0,H);
	glEnd();

	//----------------
	glutSwapBuffers();
}

/*
changes size of the window
*/
void changeSize(int w, int h) 
{
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Sets the GL_PROJECTION mtx to be identity mtx;
	glOrtho(0.0,w,0.0,h,-1.0,1.0); //Multiplies the GL_PROJECTION mtx (identity) and sets the value to the new ortho mtx.
	glScaled(1.0,-1.0,1.0); // Scales and inverts the Y axis;
	glTranslated(0.0,-h,0.0); // 	
}