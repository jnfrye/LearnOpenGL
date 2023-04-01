#version 330 core

// We must declare an output value representing the color
out vec4 FragColor;

uniform vec4 MyColor;

void main()
{
    // Just outputting a constant color
    FragColor = MyColor;
}