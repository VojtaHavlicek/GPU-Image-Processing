#include "EdgeDetectionShader40.h"
/**
*/
EdgeDetectionShader40::EdgeDetectionShader40()
{
	std::cout << "You are hapilly using EdgeDetectionShader shader, man !!!\n";
	addFragmentShaderSource("src/shaders/EdgeDetectionShader40/EdgeDetectionShader40.frag");
	addVertexShaderSource("src/shaders/EdgeDetectionShader40/EdgeDetectionShader40.vert");
}

EdgeDetectionShader40::~EdgeDetectionShader40(){}