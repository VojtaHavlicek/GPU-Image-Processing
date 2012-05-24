#include "BrightnessShader.h"
/**
*/
BrightnessShader::BrightnessShader()
{
	std::cout << "You are hapilly using Brightness shader, man !!!\n";
	addFragmentShaderSource("src/shaders/BrightnessShader/BrightnessShader.frag");
	addVertexShaderSource("src/shaders/BrightnessShader/BrightnessShader.vert");
}

BrightnessShader::~BrightnessShader(){}