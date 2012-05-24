// Fullscreen mode?
bool fullscreen = false;

//Dimensions of the window
 int W = 400.0;
 int H = 300.0;

/**
Functions
*/
//Function identifiers
void openGLDrawScene();
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