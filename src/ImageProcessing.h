// Fullscreen mode?
bool fullscreen = false;

//Dimensions of the initial window and picture
 unsigned int W = 240;
 unsigned int H = 240;

 unsigned int windowWidth = W;
 unsigned int windowHeight = H;

/**
Functions
*/
//Function identifiers
void openGLDrawScene();
void prepareShaders();
void prepareTexture();
void changeSize(int, int);
int openGLInit(GLvoid);
void setupFBO();

/**
Shader pointers
*/

GLuint vertexShader;
GLuint fragmentShader;
GLuint program;


// Pointers to application window
int win1;