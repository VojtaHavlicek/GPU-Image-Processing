// ShaderProgram.cpp
//
// Class for fast inclusion of the shaders and storing data about them.
// Made as a part of the summer term project.
//
// Vojta Havlicek 2012
/////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS

#include "ShaderProgram.h"
#include <cstring>
#include "../textfile/textfile.h"     // includes textfile manipulation utilities



ShaderProgram::ShaderProgram(void)
{
	programPrepared = false; // if constructed, set programPrepared to false;
	programRunning  = false;
	programLinked = false;
}

ShaderProgram::~ShaderProgram(void)
{
}

/**
adds shader sources to be applied
*/
void ShaderProgram::addFragmentShaderSource(std::string src) 
{
	/**
	slow conversion str -> cstring
	*/

	char * filename = new char [src.length()+1];
	strcpy(filename, src.c_str());
	

	fragmentShaderSources.push_back(textFileRead(filename));
}

void ShaderProgram::addVertexShaderSource(std::string src) 
{
	char * filename = new char [src.length()+1];
	strcpy(filename, src.c_str());
	

	vertexShaderSources.push_back(textFileRead(filename));
}

/**
Prepares the glProgram to be later used
*/
void ShaderProgram::prepareProgram() 
{
	program = glCreateProgram();

	// Goes through the whole vertexShaderSources vector using iterator logic. 
	for(std::vector<char*>::iterator it = vertexShaderSources.begin(); it != vertexShaderSources.end(); ++it)
	{
		
		//std::cout << "Test trace from shader program" << *it << "\n";
		char* source = *it;									              // links source to a new var;
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);	          // creates a shader;

		const char* constSource = source;
		glShaderSource(vertexShader,   1, &constSource, NULL);                 // attachess source to the shader;
		free(source);													  // frees the memory occupied by sourcecode;

		glCompileShader(vertexShader);									  // compiles the shader
		glAttachShader(program, vertexShader);							  // attaches the shader to the program
	}
	

	// Iterates through the whole fragmentShader vector
	for(std::vector<char*>::iterator it = fragmentShaderSources.begin(); it != fragmentShaderSources.end(); ++it)
	{
		
		//std::cout << "Test trace from shader program" << *it << "\n";
		char* source = *it;									                  // links source to a new var;
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	          // creates a shader;

		const char* constSource = source;
		glShaderSource(fragmentShader,   1, &constSource, NULL);              // attachess source to the shader;
		free(source);													      // frees the memory occupied by sourcecode;

		glCompileShader(fragmentShader);									  // compiles the shader
		glAttachShader(program, fragmentShader);							  // attaches the shader to the program
	}

	/**
	Binds everything needed
	*/
	
	width  = glGetUniformLocationARB(program, "width");
	height = glGetUniformLocationARB(program, "height");
	time   = glGetUniformLocationARB(program, "time");
	tex    = glGetUniformLocationARB(program, "tex");
	programPrepared = true;
}

int ShaderProgram::use()
{
	if(programPrepared)
	{
		glUseProgram(program); // run
		return 1;
	}
	return 0;
}

int ShaderProgram::link()
{
	if(programPrepared){
		glLinkProgram(program);
		programLinked = true;
		return 1;
	}
	return 0;
}
/**
If program is prepared, runs the shader program
*/
int ShaderProgram::run()
{
	if(programPrepared){
		glLinkProgram(program); //link 
		glUseProgram(program); // run
		programRunning = true;
		return 1;
	}

	return 0;
}

/**
seters for common uniforms;
*/
using std::cout;

void ShaderProgram::setWidth(GLfloat W)
{
	if(width != -1)
		glUniform1fARB(width, W);
	else
		cout<<"WARNING: width uniform is not defined in target shader!\n";
}
	
void ShaderProgram::setHeight(GLfloat H)
{
	if(height != -1)
		glUniform1fARB(height, H);
	else
		cout<<"WARNING: height uniform is not defined in target shader!\n";
}

void ShaderProgram::setTex(GLint handler)
{
	if(tex != -1)
		glUniform1iARB(tex, GL_TEXTURE0_ARB); 
	else
	{ 
		tex    = glGetUniformLocationARB(program, "tex");
		if(tex == -1)
			cout << "PRIORITY WARNING: tex uniform is not defined in target shader!\n";
		else
			glUniform1iARB(tex, GL_TEXTURE0_ARB); 
	}
}

void ShaderProgram::setTime(GLfloat value)
{
	if(time != -1)
		glUniform1fARB(time, value);
	else
		cout<<"PRIORITY WARNING: time uniform is not defined in target shader!\n";
}