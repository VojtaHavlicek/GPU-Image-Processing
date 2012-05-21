#include "MonoColorShader.h"
/**
*/
MonoColorShader::MonoColorShader()
{
	
	addFragmentShaderSource("src/shaders/monoColorTest/testFragmentShader.frag");
	addVertexShaderSource("src/shaders/monoColorTest/testVertexShader.vert");
}

MonoColorShader::~MonoColorShader(){}