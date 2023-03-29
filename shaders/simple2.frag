#version 330 core

// We must declare an output value representing the color
out vec4 FragColor;

void main()
{
    // Just outputting a constant color
    FragColor = vec4(0.5f, 0.2f, 1.0f, 1.0f);
}