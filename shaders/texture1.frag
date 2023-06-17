#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D TexData0;
uniform sampler2D TexData1;

void main()
{
	FragColor = mix(texture(TexData0, TexCoord), texture(TexData1, TexCoord), 0.5);
}