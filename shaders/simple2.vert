#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aPhaseOffset;

uniform float Phase;

out vec4 VertColor;

void main()
{
	vec3 colors[3] = {
		vec3(1.f, 0.f, 0.f),
		vec3(0.f, 1.f, 0.f),
		vec3(0.f, 0.f, 1.f)
	};

	float curPhase = aPhaseOffset + Phase - floor(aPhaseOffset + Phase);
	float scaledPhase = curPhase * colors.length();
	int startIndex = int(floor(curPhase * colors.length()));
	float subPhase = scaledPhase - startIndex;

	VertColor = vec4(mix(colors[startIndex], colors[(startIndex + 1) % colors.length()], subPhase), 1.f);

	gl_Position = vec4(aPos, 1.0);
}