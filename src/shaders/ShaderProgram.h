// ShaderProgram.h
//
// Interface for the class for fast inclusion of the shaders and storing data about them.
// Made as a part of the summer term project.
//
// Vojta Havlicek 2012
/////////////////////////////////////////////////////////////////////////

#include <GL/glew.h> // header file of GLEW;
#include <GL/glut.h> // header file of GLUT functions
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

	void prepareProgram(); //Prepares the shader program to be later used

	int run(); // Runs the attached program. Returns 1 on succes, 0 on fail (if program was not prepared); 

	GLuint program;       // stores a handler to OpenGL program

	/*
	^^^ it is important that program cannot be private as it is required for modifying uniform/attribute variables within the shader from outside the shader
	*/

	bool programPrepared; // bool to determine if the program was prepared

private : 
	std::vector<char*> fragmentShaderSources; //contains info about the fragmentShader files compiled into the program
	std::vector<char*> vertexShaderSources;   //contains info about the   vertexShader files compiled into the program

};

