#type vertex
#version 430 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in vec4 aColor;

out vec2 TexCoords;

void main() {
	TexCoords = aTexCoords;

	gl_Position = vec4(aPosition, 1.0);
}


#type fragment
#version 430 core

layout(location = 0) out vec4 finalColor;

in vec2 TexCoords;

uniform sampler2D image;
uniform bool flipHorizontal;
uniform bool flipVertical;

void main() {
	vec2 sampleCoords = TexCoords;
	if (flipHorizontal) {
		sampleCoords.x = 1.0 - sampleCoords.x;
	}
	if (flipVertical) {
		sampleCoords.y = 1.0 - sampleCoords.y;
	}
	finalColor = texture(image, sampleCoords);
}
