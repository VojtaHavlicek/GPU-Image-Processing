
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
	
	vec4  color = vec4(0.0,0.0,0.0,0.0);
	float factor = 1.0;
	
	

	int Y = 0;
	int X = 0;

	if(x() > width/2){
	for(Y = -3; Y <= 3; Y++)
	{
		for(X = -3; X <= 3; X++)
		{


			if(X*X == 1 || Y*Y == 1)
			{
				factor = 50.0;
			}

			if(X*X == 4 || Y*Y == 4)
			{
				factor = 20.0;
			}

			if(X*X == 9 || Y*Y == 9)
			{
				factor = 10.0;
			}

			/**
			Corner texels
			*/

			if(X*X == Y*Y)
			{
				factor *= 0.7;
			}


			/**
			Center texel (biggest priority)
			*/
			if(X == 0 && Y == 0)
			{
				factor = 20;
			}

			color += getPixel(X,Y)*factor*(1.0/512.0);
		}
	}
		color *= 1.5;
	}
	
	for(Y = -3; Y <= 3; Y++)
	{
		for(X = -3; X <= 3; X++)
		{
			

			if(X*X == 1 || Y*Y == 1)
			{
				factor = -1;
			}

			if(X*X == 4 || Y*Y == 4)
			{
				factor = -.5;
			}

			if(X*X == 9 || Y*Y == 9)
			{
				factor = -1;
			}

			/**
			Corner texels
			*/
			if(X*X == Y*Y)
			{
				factor *= 0.7;
			}

			/**
			Center texel (biggest priority)
			*/
			if(X == 0 && Y == 0)
			{
				factor = sin(time/5)*2 + 32;
			}

			color += getPixel(X,Y)*factor;
		}
	}

	gl_FragColor = color;
}

