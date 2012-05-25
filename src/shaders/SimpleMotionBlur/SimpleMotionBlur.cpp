#include "SimpleMotionBlur.h"
/**
*/
SimpleMotionBlur::SimpleMotionBlur()
{
	std::cout << "You are hapilly using SimpleMotionBlur shader, man !!!\n";
	addFragmentShaderSource("src/shaders/SimpleMotionBlur/SimpleMotionBlur.frag");
	addVertexShaderSource("src/shaders/SimpleMotionBlur/SimpleMotionBlur.vert");
}

SimpleMotionBlur::~SimpleMotionBlur(){}