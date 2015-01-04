#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec4 color;

varying vec4 color0;
varying vec2 texCoord0;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1);
    texCoord0 = texCoord;
    color0 = color;
}
