#include "ShakeShader.h"
/**
*/
ShakeShader::ShakeShader()
{
	std::cout << "You are hapilly using ShakeShader shader, man !!!\n";
	addFragmentShaderSource("src/shaders/ShakeShader/ShakeShader.frag");
	addVertexShaderSource("src/shaders/ShakeShader/ShakeShader.vert");
}

ShakeShader::~ShakeShader(){}