attribute vec4 gl_Color;
varying vec4 gl_FrontColor;
varying vec4 gl_BackColor;


void main()
{	

	gl_FrontColor = gl_Color;
	// the following three lines provide the same result

//	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
//	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_Position = ftransform();
}
