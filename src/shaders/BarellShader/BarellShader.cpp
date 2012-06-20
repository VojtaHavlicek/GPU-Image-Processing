#include "BarellShader.h"
/**
*/
BarellShader::BarellShader()
{
	std::cout << "You are hapilly using BarellShader, man !!!\n";
	addFragmentShaderSource("src/shaders/BarellShader/BarellShader.frag");
	addVertexShaderSource("src/shaders/BarellShader/BarellShader.vert");
}

BarellShader::~BarellShader(){}