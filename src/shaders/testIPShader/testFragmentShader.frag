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

/*
*/

void main()
{
	vec4 color;

	if(x() < width*.5){
		color = getPixel(0,0)*0.5;
	}else{
		color = getPixel(0,0);
	}

	gl_FragColor = color; 
}
