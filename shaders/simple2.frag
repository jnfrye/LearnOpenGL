#version 330 core

// Demonstrating how outputs from vert shader are passed as inputs to frag shader
in vec4 VertColor;

out vec4 FragColor;

void main()
{
    FragColor = VertColor;
}