#include "GaussianShader.h"
/**
*/
GaussianShader::GaussianShader()
{
	std::cout << "You are hapilly using Gaussian shader, man !!!\n";
	addFragmentShaderSource("src/shaders/gaussianBlurTest/GaussianShader.frag");
	addVertexShaderSource("src/shaders/gaussianBlurTest/GaussianShader.vert");
}

GaussianShader::~GaussianShader(){}