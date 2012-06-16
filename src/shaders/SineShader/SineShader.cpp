#include "SineShader.h"
/**
*/
SineShader::SineShader()
{
	std::cout << "You are hapilly using Sine shader, man !!!\n";
	addFragmentShaderSource("src/shaders/SineShader/SineShader.frag");
	addVertexShaderSource("src/shaders/SineShader/SineShader.vert");
}

SineShader::~SineShader(){}