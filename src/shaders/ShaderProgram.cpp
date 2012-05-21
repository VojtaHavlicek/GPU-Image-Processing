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

	programPrepared = true;
}

/**
If program is prepared, runs the shader program
*/

int ShaderProgram::run()
{
	if(programPrepared)
	{
		glLinkProgram(program); //link 
		glUseProgram(program); // run
		return 1;
	}

	return 0;
}