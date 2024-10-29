#type vertex
#version 430 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;
layout(location = 3) in vec4 aColor;

out vec2 TexCoords;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
	TexCoords = aTexCoords;

	gl_Position = projectionMatrix * viewMatrix * vec4(aPosition, 1.0);
}


#type fragment
#version 430 core

layout(location = 0) out vec4 finalColor;

in vec2 TexCoords;

uniform sampler2D image[16];

void main() {
	vec2 sampleCoords = TexCoords;
	finalColor = texture(image[0], sampleCoords);
}
