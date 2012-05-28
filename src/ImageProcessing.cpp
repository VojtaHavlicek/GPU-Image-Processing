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

#include <Windows.h>
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
/*
void setupFBO(){
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);
 
	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
 
	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
 
	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
 
	// Set the list of draw buffers.
	GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "Framebuffers empty";
}
*/




GLuint EmptyTexture(GLuint wi, GLuint he)                           // Create An Empty Texture
{
    GLuint txtnumber;                       // Texture ID
    unsigned int* data;                     // Stored Data
 
    // Create Storage Space For Texture Data (128x128x4)
    data = (unsigned int*)new GLuint[((wi * he)* 4 * sizeof(unsigned int))];
    ZeroMemory(data,((wi * he)* 4 * sizeof(unsigned int)));   // Clear Storage Memory
 
    glGenTextures(1, &txtnumber);                   // Create 1 Texture
    glBindTexture(GL_TEXTURE_2D, txtnumber);            // Bind The Texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, wi, he, 0,
     GL_RGBA, GL_UNSIGNED_BYTE, data);           // Build Texture Using Information In data
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
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


unsigned int myTexture;

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
	myTexture = EmptyTexture(240, 240);
	//prepareShaders();  //shaders disabled while trying out textures

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
}


/**
Entry point for shader program production
*/
//--- handlers to shaders

ShaderProgram shaderProgram;

void prepareShaders()
{
	shaderProgram = EdgeDetectionShader20();
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
	textureHandler = SOIL_load_OGL_texture("src/dan.png",
							SOIL_LOAD_AUTO,
							SOIL_CREATE_NEW_ID,
							NULL);
	
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
GLuint myFBO = 0;

void openGLDrawScene() 
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	

	
	cout << myTexture;
	glGenFramebuffersEXT(1, &myFBO);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, myFBO);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, myTexture, 0);


	glBindTexture(GL_TEXTURE_2D, textureHandler);


	shaderProgram = GaussianShader();
	shaderProgram.prepareProgram();
	openGLInitScene();


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


	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
	


	glBindTexture(GL_TEXTURE_2D, myTexture);

	shaderProgram = EdgeDetectionShader();
	shaderProgram.prepareProgram();
	openGLInitScene();


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