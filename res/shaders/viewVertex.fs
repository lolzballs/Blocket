#version 120

varying vec2 texCoord0;
varying vec4 color0;

uniform sampler2D sampler;

void main()
{
    vec4 texColor = texture2D(sampler, texCoord0);
	if (color0 == vec4(0, 0, 0, 0))
	{
		gl_FragColor = texColor;
	}
	else
	{
		gl_FragColor = texColor * color0;
	}
}