#type vertex
#version 430 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec4 aColor;

out vec2 TexCoords;
out vec4 Color;

void main() {
	TexCoords = aTexCoords;
	Color = aColor;

	gl_Position = vec4(aPosition, 1.0);
}


#type fragment
#version 430 core

layout(location = 0) out vec4 finalColor;

in vec2 TexCoords;
in vec4 Color;

uniform vec3 tempColor;
uniform float alpha;

void main() {
	finalColor = vec4(tempColor, alpha) * Color;
}
