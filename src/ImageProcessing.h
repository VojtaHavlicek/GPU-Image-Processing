// Fullscreen mode?
bool fullscreen = false;

//Dimensions of the window
 int W = 240;
 int H = 240;

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