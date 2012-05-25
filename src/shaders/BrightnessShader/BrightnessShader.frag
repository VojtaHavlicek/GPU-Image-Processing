uniform sampler2D tex;
uniform float brightness = 0.5;

void main()
{
	vec4 texel     = texture2D(tex, gl_TexCoord[0].st);
	vec4 color     = texel*(gl_TexCoord[0].x);

	gl_FragColor = color;
}
