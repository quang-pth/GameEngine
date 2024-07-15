#type vertex
#version 430 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec3 aColor;

out vec3 Position;
out vec2 TexCoords;
out vec3 Color;

void main()
{
	TexCoords = aTexCoords;
	Position = aPosition;
	Color = aColor;

	gl_Position = vec4(aPosition, 1.0);
}

#type fragment
#version 430 core

layout(location = 0) out vec4 finalColor;

in vec3 Position;
in vec2 TexCoords;
in vec3 Color;

uniform vec3 tempColor;
uniform float alpha;

void main()
{
	finalColor =  vec4(tempColor, alpha) * vec4(Color, 1.0f);
}