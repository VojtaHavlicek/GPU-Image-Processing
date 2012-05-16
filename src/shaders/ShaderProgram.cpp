// ShaderProgram.cpp
//
// Class for fast inclusion of the shaders and storing data about them.
// Made as a part of the summer term project.
//
// Vojta Havlicek 2012
/////////////////////////////////////////////////////////////////////////
#include "ShaderProgram.h"
#include <cstring>
#include "../textfile/textfile.h"     // includes textfile manipulation utilities

ShaderProgram::ShaderProgram(void)
{

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


