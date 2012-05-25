#include "EdgeDetectionShader.h"
/**
*/
EdgeDetectionShader::EdgeDetectionShader()
{
	std::cout << "You are hapilly using EdgeDetectionShader shader, man !!!\n";
	addFragmentShaderSource("src/shaders/EdgeDetectionShader/EdgeDetectionShader.frag");
	addVertexShaderSource("src/shaders/EdgeDetectionShader/EdgeDetectionShader.vert");
}

EdgeDetectionShader::~EdgeDetectionShader(){}