#type vertex
#version 430 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;

out vec3 Position;
out vec2 TexCoords;

void main()
{
	TexCoords = aTexCoords;
	Position = aPosition;

	gl_Position = vec4(aPosition, 1.0);
}

#type fragment
#version 430 core

layout(location = 0) out vec4 finalColor;

in vec3 Position;
in vec2 TexCoords;

void main()
{
	finalColor = vec4(Position, 1.0f);
}