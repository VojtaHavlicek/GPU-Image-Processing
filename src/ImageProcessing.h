// Fullscreen mode?
bool fullscreen = false;

//Dimensions of the window
float W = 400.0;
float H = 300.0;

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