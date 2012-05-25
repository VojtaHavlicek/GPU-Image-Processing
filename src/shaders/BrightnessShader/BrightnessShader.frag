uniform sampler2D tex;
uniform float time = 0.0;

void main()
{
	vec4 texel     = texture2D(tex, gl_TexCoord[0].st);
	vec4 color     = texel*(sin(time)/2 + .5);
	gl_FragColor = color;
}
