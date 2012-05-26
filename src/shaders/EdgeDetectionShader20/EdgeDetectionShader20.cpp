#include "EdgeDetectionShader20.h"
/**
*/
EdgeDetectionShader20::EdgeDetectionShader20()
{
	std::cout << "You are hapilly using EdgeDetectionShader shader, man !!!\n";
	addFragmentShaderSource("src/shaders/EdgeDetectionShader20/EdgeDetectionShader20.frag");
	addVertexShaderSource("src/shaders/EdgeDetectionShader20/EdgeDetectionShader20.vert");
}

EdgeDetectionShader20::~EdgeDetectionShader20(){}