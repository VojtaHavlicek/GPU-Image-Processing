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
#include "textfile.h"  

//
// Uses the standard namespace for io operations
//
using namespace std;

// Pointers to application window
int win1;

// Fullscreen mode?
bool fullscreen = false;

//Dimensions of the window
float W = 512.0;
float H = 512.0;

/**
Functions
*/
//Function identifiers
void openGLDrawScene();
void prepareShaders();
int openGLInit(GLvoid);

//
// Funkce vstupu klavesnice
//
void onKeyboard(unsigned char key, int x, int y)
{
	key=(key>'A' && key<='Z') ? key+'a'-'A':key; // prevod na mala pismena
    switch (key) {
		
		//--- EXIT CASES
        case 'x':                       // stlaceni techto klaves uzavre aplikaci
        case 'q':
        case 27:                        // 27 je kod klavesy ESC
            exit(0);
        break;
        
		//----------------------------------
		case 'f':  // klavesa 'f' zpusobi
			if(!fullscreen){
				fullscreen = true;
				glutFullScreen();           // prepnuti na celou obrazovku
			}else{
				glutReshapeWindow(W, H);// zmenseni okna
				glutPositionWindow(200, 200);
				fullscreen = false;
			}

        break;
    }
}

//---------------------------------------------------------------------
// Hlavni funkce konzolove aplikace
//---------------------------------------------------------------------
int main(int argc, char **argv)
{
	cout << "Image Processing Using GPU \n\nCreated by Vojtech Havlicek & Daniel Greening (2012)\nSupervised by Lionel Fachkamps\nImperial College\n---\nOutput:\n";
	/**
	Prepares GLUT
	*/
    glutInit(&argc, argv);              // inicializace knihovny GLUT
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(W,H);
	glutInitWindowPosition(200,200);

	/**
	Create the new Window
	*/
    win1 = glutCreateWindow("Image Processing Project");// vytvoreni okna pro kresleni
	
	glutDisplayFunc(openGLDrawScene);         // registrace funkce volane pri prekreslovani okna
	glutIdleFunc(openGLDrawScene);
	
	glEnable(GL_DEPTH_TEST);
	glClearColor(.5,.5,.5,1.0);
	glEnable(GL_CULL_FACE);

	openGLInit();
	glewInit();

	if(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	{
		cout << "Shaders supported" << "\n";
	}

	/**
	Pre-run application entry point
	*/

	prepareShaders();

	/**
	Starts the main GLUT loop
	*/
	glutMainLoop(); //starts the main loop of the app.

    return 0;                           // navratova hodnota vracena operacnimu systemu
}


/**
Initialization function for openGL. Setups the OpenGL in the beginning.
Check if it does not collide with GLUT initialization.
*/

int openGLInit(GLvoid)
{
	glShadeModel(GL_SMOOTH); //Enables smooth shading

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Make perspective corrections
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return 0;
}


/**
Entry point for shader program production
*/
//--- handlers to shaders
GLuint testVertexShader;
GLuint testFragmentShader;
GLuint testProgram;

void prepareShaders()
{
	cout << "---\nPREPARING SHADERS: \n";
	cout << "\nPROGRAM\n";
	cout << "Preparing the shader program: ";
	testProgram = glCreateProgram();
	cout << "Success\n";
	
	char * testVertexShaderSource;
	char * testFragmentShaderSource;

	/**
	VertexShader definition HERE
	----------------------------
	*/
	cout << "\nVERTEX SHADER\n";
	testVertexShader       = glCreateShader(GL_VERTEX_SHADER);                // Creates Shader
	cout << "Reading the shader source: ";
	testVertexShaderSource = textFileRead("shaders/testVertexShader.vert");   // Loads Source. Uses textfile header file;
	cout << "Success\n";
	const char * testVertexShaderSourcePointer = testVertexShaderSource;      // Grabs a reference to source loaded
	
	glShaderSource(testVertexShader, 1, &testVertexShaderSourcePointer, NULL); // Why reference and why NULL for lengths ?
	free(testVertexShaderSource);  // Frees the memory used by the sourcefile for shader
	cout << "Compiling the shader: ";
	glCompileShader(testVertexShader); // Compiles
	cout << "Success \n";

	cout << "Attaching to the program: ";
	glAttachShader(testProgram, testVertexShader);                             // Attaches Shader to the program
	cout << "Success \n";

	/**
	FragmentShader definition HERE
	------------------------------
	*/
	cout << "\nFRAGMENT SHADER\n";
	testFragmentShader       = glCreateShader(GL_FRAGMENT_SHADER);
	cout << "Reading the shader source: ";
	testFragmentShaderSource = textFileRead("shaders/testFragmentShader.frag");
	cout << "Success\n";

	const char * testFragmentShaderSourcePointer = testFragmentShaderSource; 
	
	glShaderSource(testFragmentShader, 1, &testFragmentShaderSourcePointer, NULL); //Why reference and why NULL?
	free(testFragmentShaderSource);
	cout << "Compiling the shader: ";
	glCompileShader(testFragmentShader);
	cout << "Success \n";

	cout << "Attaching to the program: ";
	glAttachShader(testProgram, testFragmentShader);
	cout << "Success \n";
	
	/**
	Link here
	*/
	glLinkProgram(testProgram);

	/**
	Use here ??? glUseProgram(testProgram);
	*/
	glUseProgram(testProgram);

}

//-----------------------------------------------------------------------------------------
//
//	An entry point function for all OpenGL drawing. Called at onDisplay.
//
float lpos[4] = {1,0.5,1,0};
float a = 0.0;
void openGLDrawScene() 
{
	/**
	Entry Point For Rendering And GL Here
	*/	

	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ???

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex2f(-0.5,-0.5);
		//glColor3f(0.0f,1.0f,0.0f);
		glVertex2f(0.5,0.0);
		glColor3f(0.0f,1.0f,1.0f);
		glVertex2f(0.0,0.5);
	glEnd();
	/*
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glRotatef(a,0,1,1);
	glutSolidTeapot(1);
	a+=0.1;
	*/
	
	glutSwapBuffers();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);


}