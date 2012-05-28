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



GLuint EmptyTexture(GLuint wi, GLuint he)                           // Create An Empty Texture. This is stolen from a NeHe tutorial.
{
    GLuint txtnumber;                       // Texture ID
    unsigned int* data;                     // Stored Data
	
	
    // Create Storage Space For Texture Data (128x128x4)
    data = (unsigned int*)new GLuint[((wi * he)* 4 * sizeof(unsigned int))];
    memset(data,0,((wi * he)* 4 * sizeof(unsigned int)));   // Clear Storage Memory osing ZeroMemory
 
    glGenTextures(1, &txtnumber);                   // Create 1 Texture
    glBindTexture(GL_TEXTURE_2D, txtnumber);            // Bind The Texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, wi, he, 0,
     GL_RGBA, GL_UNSIGNED_BYTE, data);           // Build Texture Using Information In data
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //are the filters neccesarry??
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 
    delete [] data;                         // Release data
 
    return txtnumber;                       // Return The Texture ID
}


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


unsigned int myTexture; // this is the texture that the framebuffer object renders to

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
	//glutIdleFunc(openGLDrawScene);
	glutKeyboardFunc(onKeyboard);
	glutReshapeFunc(changeSize);
	
	glClearColor(0.0,0.0,0.0,1.0);
	
	glewInit();

	if(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		cout << "ARB extensions supported" << "\n";
	



	prepareTexture(); // prepares the texture to be displayed.
	myTexture = EmptyTexture(240, 240); // creates empty texture, using 240, 240, as don't know how to get width/height vars
	//prepareShaders();  //shaders called elsewhere

	//openGLInitScene();

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
} //this isn't used


/**
Entry point for shader program production
*/
//--- handlers to shaders

ShaderProgram shaderProgram;

void prepareShaders()
{
	shaderProgram = EdgeDetectionShader20();
	shaderProgram.prepareProgram();
} //this isn't used atm


/**
Prepares texture for later usage
*/
GLuint textureHandler;

void prepareTexture()
{
	glEnable(GL_TEXTURE_2D);
	
	glActiveTextureARB(GL_TEXTURE0);
	textureHandler = SOIL_load_OGL_texture("src/dan.png",
							SOIL_LOAD_AUTO,
							SOIL_CREATE_NEW_ID,
							SOIL_FLAG_INVERT_Y);   //added this because image was getting inverted beforehand - probably not the best solution to problem
	
	if(textureHandler == 0)
		cout << "WARNING: Texture is not loaded \n";	
}

/**
Inits the whole scene. All stuff about setting of uniforms should be done here.
*/
GLint location; //Location of Alpha
GLint width;
GLint height;
GLint brightnessLevel;

void openGLInitScene() // is this still a logical name for this function?
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
GLuint myFBO = 0; //framebuffer object handler

void openGLDrawScene() 
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	

	
	cout << "Texture to Render to ID: " << myTexture << "\n";
	glGenFramebuffersEXT(1, &myFBO); 
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, myFBO);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, myTexture, 0); //passes empty texture to framebuffer object


	glBindTexture(GL_TEXTURE_2D, textureHandler); //binds picture texture


	shaderProgram = GaussianShader(); //select shaderprogram
	shaderProgram.prepareProgram(); 
	openGLInitScene(); //runs shaderprogram and binds some uniforms


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


	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); //unbinds framebuffer object, so now rendering to backbuffer or somewhere
	


	glBindTexture(GL_TEXTURE_2D, myTexture); //binds new texture, now been processed by first shader

	shaderProgram = EdgeDetectionShader(); //selects 2nd shaderprogram
	shaderProgram.prepareProgram();
	openGLInitScene(); //runs 2nd shaderprogram and binds some uniforms


	glBegin(GL_QUADS);
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 0.0f);
		glVertex2d((windowWidth-W)/2,(windowHeight-H)/2);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 0.0f); // TexCoords are normalized, in range [0,1]
		glVertex2d((windowWidth+W)/2,(windowHeight-H)/2);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 1.0);
		glVertex2d((windowWidth+W)/2,(windowHeight+H)/2);
		
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 1.0);
		glVertex2d((windowWidth-W)/2,(windowHeight+H)/2);
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

	windowHeight = h;
	windowWidth = w;
}