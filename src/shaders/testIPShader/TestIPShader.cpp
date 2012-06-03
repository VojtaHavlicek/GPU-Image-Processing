#include "TestIPShader.h"

/**
*/
TestIPShader::TestIPShader()
{
	
	addFragmentShaderSource("src/shaders/testIPShader/testFragmentShader.frag");
	addVertexShaderSource("src/shaders/testIPShader/testVertexShader.vert");
}

TestIPShader::~TestIPShader(){}