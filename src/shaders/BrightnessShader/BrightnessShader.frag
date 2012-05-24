uniform sampler2D tex;
uniform float brightness = 0.5;

void main()
{
	vec4 texel = texture2D(tex, gl_TexCoord[0].st);
	gl_FragColor = texel*brightness;
}
