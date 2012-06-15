// Fullscreen mode?
bool fullscreen = false;

//Dimensions of the window
 int W = 320;
 int H = 240;

 int windowHeight = H;
 int windowWidth = W;
/**
Functions
*/
//Function identifiers
 //init functions
void prepareShaders();
void prepareTexture();

//camera functions
bool setupCamera();
void doSnapshot();
void shutDownCamera();
void rewriteTexData();

//openGL functions
void openGLIdle();
void openGLDrawScene();
void openGLInitScene();

//callbacks
void changeSize(int, int);
void onKeyboard(unsigned char, int, int);
int  openGLInit(GLvoid);

/**
Shader pointers
*/
GLuint textureHandler = 0;
GLuint vertexShader;
GLuint fragmentShader;
GLuint program;



// Pointers to application window
int win1;