
 
uniform sampler2D tex;
uniform int switcher = 1;
uniform float time = 0.0;
uniform float width = 240;
uniform float height = 240;
float x0;
float y0;
/*
input unnormalised valuesy
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
float X;
float Y;
float Xn;
float Yn;
float k1 = 0.010;
float k2 = 0.10;
float f=1;
void main()
{
 x0 = width *.5;
 y0 = height *.5;
 X = x()-x0;
 Y = y()-y0;
 if(switcher == 1){
 f = 1 + (X*X+Y*Y)*k1;
 }
 if(switcher == 2){
 f = 1 - sqrt(sqrt(X*X+Y*Y))*k2;
 }
 Xn = f*X;
 Yn = f*Y;
 vec4 color = getPixelAbs(Xn+x0, Yn+y0);
   
 if(Xn+x0 >= width  || Xn+x0 <= 0) color = vec4(0.0,0.0,0.0,0.0);
 if(Yn+y0 >= height || Yn+y0 <= 0) color = vec4(0.0,0.0,0.0,0.0);
 gl_FragColor = color;
}