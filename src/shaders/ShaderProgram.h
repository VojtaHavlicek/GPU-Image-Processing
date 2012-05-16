// ShaderProgram.h
//
// Interface for the class for fast inclusion of the shaders and storing data about them.
// Made as a part of the summer term project.
//
// Vojta Havlicek 2012
/////////////////////////////////////////////////////////////////////////


#include <vector>
#include <string>
#include <iostream>

#pragma once
class ShaderProgram
{
public:
	
	ShaderProgram(void);
	~ShaderProgram(void);

	void addFragmentShaderSource(std::string);  // adds a fragment shader source to the list.
	void addVertexShaderSource(std::string);    // adds a vertex shader source to the list.

	std::vector<char*> fragmentShaderSources; //contains info about the fragmentShader files compiled into the program
	std::vector<char*> vertexShaderSources;   //contains info about the   vertexShader files compiled into the program
};

