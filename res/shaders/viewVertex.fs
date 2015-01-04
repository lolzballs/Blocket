#version 120

varying vec2 texCoord0;
varying vec4 color0;

uniform sampler2D sampler;

void main()
{
    gl_FragColor = color0;
}
