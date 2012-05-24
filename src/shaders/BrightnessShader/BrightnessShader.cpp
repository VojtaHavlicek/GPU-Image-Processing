#include "BrightnessShader.h"
/**
*/
BrightnessShader::BrightnessShader()
{
	
	addFragmentShaderSource("src/shaders/BrightnessShader/BrightnessShader.frag");
	addVertexShaderSource("src/shaders/BrightnessShader/BrightnessShader.vert");
}

BrightnessShader::~BrightnessShader(){}