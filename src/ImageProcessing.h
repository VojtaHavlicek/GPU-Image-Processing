// Fullscreen mode?
bool fullscreen = false;

//Dimensions of the window
 int W = 320;
 int H = 240;

/**
Functions
*/
//Function identifiers
bool setupCamera();
void openGLDrawScene();
void openGLInitScene();
void prepareShaders();
void prepareTexture();
void changeSize(int, int);
int openGLInit(GLvoid);

/**
Shader pointers
*/

GLuint vertexShader;
GLuint fragmentShader;
GLuint program;


// Pointers to application window
int win1;