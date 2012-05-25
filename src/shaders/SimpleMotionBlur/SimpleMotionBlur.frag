
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
	/*
		-1 -1 -1
		-1  8 -1
		-1 -1 -1
	*/
	vec4  color = vec4(0.0,0.0,0.0,0.0);
	float factor = 1.0;
	
	float tempLen = 10*(0.5*(sin(time) + 1));
	int len = int (tempLen)+1;

	for(int i = 0; i < len; i++)
	{
		color += (getPixel(0,i)/len);
	}

	/*int Y;
	int X;

	for(Y = -2; Y < 2; Y++)
		for(X = -2; X < 2; X++)
		{
			if(X == 0 && Y == 0)
				factor = 16;

			if(X*X == 1 || Y*Y == 1)
				factor = -1;

			if(X*X == 4 || Y*Y == 4)
				factor = -.5;

			color += factor*getPixel(X, Y);
		} 
	}*/
	gl_FragColor = color;
}

