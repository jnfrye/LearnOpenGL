#version 330 core

// We must declare an output value representing the color
out vec4 FragColor;
in vec3 vertColor;

uniform vec4 MyColor;

void main()
{
	// Just outputting a constant color
	FragColor = vec4(vertColor, 1.0f) * MyColor;
}