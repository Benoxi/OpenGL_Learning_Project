#version 120

// varying can be shared between shaders
varying vec2 texCoord0;

attribute vec3 position;
attribute vec2 texCoord;

// uniform is a type that can be set by the CPU
uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
}