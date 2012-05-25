uniform sampler2D tex;
uniform float time = 0.0;

void main()
{
	vec4 texel     = texture2D(tex, gl_TexCoord[0].st);
	float wave_factor_x = ((sin(sin(time) - gl_TexCoord[0].x*10) + 1)/2);
	float wave_factor_y = ((sin(time - gl_TexCoord[0].y*2) + 1)/2);
	vec4 color     = texel;
	color.x *= wave_factor_x;
	color.y *= wave_factor_y;
	gl_FragColor = color;
}
