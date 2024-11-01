#type vertex
#version 430 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in int aTextureID;
layout(location = 3) in int aFlipVertical;
layout(location = 4) in int aFlipHorizontal;

out vec2 TexCoords;
out flat int TextureID;
out flat int FlipVertical;
out flat int FlipHorizontal;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
	TexCoords = aTexCoords;
	TextureID = aTextureID;
	FlipVertical = aFlipVertical;
	FlipHorizontal = aFlipHorizontal;

	gl_Position = projectionMatrix * viewMatrix * vec4(aPosition, 1.0);
}


#type fragment
#version 430 core

layout(location = 0) out vec4 finalColor;

in vec2 TexCoords;
in flat int TextureID;
in flat int FlipVertical;
in flat int FlipHorizontal;

uniform sampler2D textures[16];

void main() {
	vec2 sampleCoords = TexCoords;

	if (FlipVertical == 1) {
		sampleCoords.y = 1.0 - sampleCoords.y;
	}

	if (FlipHorizontal == 1) {
		sampleCoords.x = 1.0 - sampleCoords.x;
	}

	finalColor = texture(textures[TextureID], sampleCoords);
}
