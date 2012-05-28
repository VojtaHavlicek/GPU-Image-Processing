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

	int use();
	int link();

	GLuint program;       // stores a handler to OpenGL program

	/*----
	uniform binds
	*/
	GLuint  tex;	      // stores a handler to texture;
	GLuint width;        // handler to width;
	GLuint height;		  // handler to height;
	GLuint time;		  // handler to time

	void setWidth(GLfloat);
	void setHeight(GLfloat);
	void setTex(GLint);
	void setTime(GLfloat);
	/*
	^^^ it is important that program cannot be private as it is required for modifying uniform/attribute variables within the shader from outside the shader
	*/
	bool programLinked;
	bool programPrepared; // bool to determine if the program was prepared
	bool programRunning;
private : 
	int run(); // deprecated and hidden from you :D 
	std::vector<char*> fragmentShaderSources; //contains info about the fragmentShader files compiled into the program
	std::vector<char*> vertexShaderSources;   //contains info about the   vertexShader files compiled into the program

};

