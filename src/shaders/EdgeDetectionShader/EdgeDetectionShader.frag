
uniform sampler2D tex;
uniform float time = 0.0;

uniform float width = 240;
uniform float height = 240;

/*
input unnormalised values.
returns pixel value of the pixel dx and dy relatively to the processed one
*/
vec4 getPixel(float dx, float dy)
{
	return  texture2D(tex, gl_TexCoord[0].st + vec2(dx/width, dy/height));
}

void main()
{
	vec4 color = 4*getPixel(0, 0) - getPixel(-1,0) - getPixel(1,0) - getPixel(0,-1) - getPixel(0,1);
	gl_FragColor = color;
}

