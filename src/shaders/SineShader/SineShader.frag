uniform sampler2D tex;
uniform float time = 0.0;


uniform float width = 240;
uniform float height = 240;

/*
input unnormalised values
*/
vec4 getPixel(float dx, float dy)
{
	return  texture2D(tex, gl_TexCoord[0].st + vec2(dx/width, dy/height));
}

/*
getsPixel absolutely
*/
vec4 getPixelAbs(float x, float y)
{
	return texture2D(tex, vec2(x/width, y/height));
}

/**
returns normalised coords of the processed pixel
*/
float x()
{
	return width*gl_TexCoord[0].x;
}

float y()
{
	return height*gl_TexCoord[0].y;
}

//-----------------

void main()
{
	vec4 texel     = texture2D(tex, vec2(gl_TexCoord[0].x + 0.01*sin(time*50+sin(time*10)*y()/20), gl_TexCoord[0].y));	
	vec4 color     = texel;//*(sin(time)/2 + .5);
	gl_FragColor = color;
}
