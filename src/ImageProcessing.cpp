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
// OpenCV
// Copyright (c) , <OWNER>
// All rights reserved.
// 
//---------------------------------------------------------------------
//#include <fdlib.h>                // face detection library
#include <cv.h>                   // cv lib
#include <highgui.h>			  // highgui 
#include <GL/glew.h>              // header file of GLEW;
#include <GL/glut.h>              // header file of GLUT functions
#include <iostream>               // input/output stream for debug
#include <string>
#include <cmath>
#include "textfile/textfile.h"     // includes textfile manipulation utilities
#include "shaders/Shaders.h"       // includes the ShaderProgram Class
#include "soil/SOIL.h"             // Soil 
#include <time.h>                  // clock
//-------------------------------------------
#include "ImageProcessing.h"       // includes interface for the file (function definitions). Always include as last !!!


/*
Main entry point
*/
int main(int argc, char **argv)
{
	std::cout << "Image Processing Using GPU \n\nCreated by Vojtech Havlicek & Daniel Greening (2012)\nSupervised by Lionel Fafchamps\nImperial College\n---\nOutput:\n";
	
	/**
	Prepares GLUT
	*/
    glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(W,H);
	glutInitWindowPosition(200,200);
    win1 = glutCreateWindow("Image Processing Project");
	
	std::cout << "OpenGL version: "<< glGetString(GL_VERSION) << "\n";  // Check for OpenGL version
	
	glutDisplayFunc(openGLDrawScene);      
	glutIdleFunc(openGLIdle);
	glutKeyboardFunc(onKeyboard);
	glutReshapeFunc(changeSize);
	glClearColor(0.0,0.0,0.0,1.0);
	
	glewInit();

	if(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		std::cout << "ARB extensions supported" << "\n";
	


	doSnapshot();
	prepareTexture(); // prepares the texture to be displayed.
	prepareShaders();  //shaders disabled while trying out textures

	openGLInitScene();
	glutMainLoop(); //starts the main loop of the app.
	
    return 0;             
}

/*
Does a snapshot using the camera
*/ 
cv::VideoCapture cap(0);
cv::Mat frame;
void doSnapshot()
{  
  if(cap.isOpened())
  {
	 cap >> frame;
	 if(W != frame.cols || H != frame.rows)
	 {
		W = frame.cols;
		H = frame.rows;
		glutReshapeWindow(W,H);
	 }
  }
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
Executed on idle state of GLUT window.
*/
clock_t last;
clock_t now;
double diffClock = 1.0;
void openGLIdle() 
{
	/**
	measure time elapsed
	*/
	now = clock();
	if(last != NULL)
		diffClock = 1000*(now - last)/CLOCKS_PER_SEC;
	last = clock();	

	openGLDrawScene();
	doSnapshot();
	rewriteTexData();

	//wait for a while. 50 ms
	/*while(1000*(clock() - now)/CLOCKS_PER_SEC < 15)
	{
	}*/
		
	
}

void rewriteTexData()
{
	glBindTexture(GL_TEXTURE_2D, textureHandler);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,frame.cols,frame.rows,0,GL_BGR,GL_UNSIGNED_BYTE,frame.ptr());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
}
/**
Entry point for shader program production
*/
//--- handlers to shaders

ShaderProgram shaderProgram;
void prepareShaders()
{
	shaderProgram = SineShader();//EdgeDetectionShader();//SineShader();//ShakeShader();
	shaderProgram.prepareProgram();
}


/**
Prepares texture for later usage
*/
void prepareTexture()
{
	glEnable(GL_TEXTURE_2D);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glGenTextures(1,&textureHandler);  
	
	rewriteTexData();
	
	if(textureHandler == 0)
		std::cout << "WARNING: Texture is not loaded \n";	
}

/**
Inits the whole scene. All stuff about setting of uniforms should be done here.
*/

GLint location; //Location of Alpha
GLint width;
GLint height;
GLint timeUniform;
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
double ratio = 1;
double a = 0;
void openGLDrawScene() 
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glBindTexture(GL_TEXTURE_2D, textureHandler); 
	
	timeUniform = glGetUniformLocationARB(shaderProgram.program, "time");
			    glUniform1fARB(timeUniform, (GLfloat)(a));
				
	a += 0.01;//*diffClock;

	glBegin(GL_QUADS);
		glColor3f(0.0,0.0,0.0);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 0.0f);
		glVertex2d((windowWidth-ratio*W)/2,(windowHeight-ratio*H)/2);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 0.0f); // TexCoords are normalized, in range [0,1]
		glVertex2d((windowWidth+ratio*W)/2,(windowHeight-ratio*H)/2);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0, 1.0);
		glVertex2d((windowWidth+ratio*W)/2,(windowHeight+ratio*H)/2);

		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 1.0);
		glVertex2d((windowWidth-ratio*W)/2,(windowHeight+ratio*H)/2);
	glEnd();

	//----------------
	glutSwapBuffers();
}




/**
keyboard utility
*/

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
		//----------------------------------
		case 'd':
			if(ratio == 1)
				ratio = 1.5;
			else
				ratio = 1;
		break;
    }
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
	glScaled(-1.0,-1.0,1.0); // Scales and inverts the Y axis and X axis too (to have a mirror effect);
	glTranslated(-w,-h,0.0); // 	

	windowHeight = h;
	windowWidth = w;
}
