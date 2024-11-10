#type vertex
#version 430 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoords;
layout(location = 2) in int aTextureID;
layout(location = 3) in int aFlipVertical;
layout(location = 4) in int aFlipHorizontal;
layout(location = 5) in vec4 aColor;

out vec2 TexCoords;
out flat int TextureID;
out flat int FlipVertical;
out flat int FlipHorizontal;
out vec4 Color;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
	TexCoords = aTexCoords;
	TextureID = aTextureID;
	FlipVertical = aFlipVertical;
	FlipHorizontal = aFlipHorizontal;
	Color = aColor;

	gl_Position = projectionMatrix * viewMatrix * vec4(aPosition, 1.0);
}


#type fragment
#version 430 core

layout(location = 0) out vec4 finalColor;

in vec2 TexCoords;
in flat int TextureID;
in flat int FlipVertical;
in flat int FlipHorizontal;
in vec4 Color;

uniform sampler2D textures[32];

void main() {
	vec2 sampleCoords = TexCoords;

	if (FlipVertical == 1) {
		sampleCoords.y = 1.0 - sampleCoords.y;
	}

	if (FlipHorizontal == 1) {
		sampleCoords.x = 1.0 - sampleCoords.x;
	}

    switch (TextureID) {
        case 0: finalColor = texture(textures[0], sampleCoords); break;
        case 1: finalColor = texture(textures[1], sampleCoords); break;
        case 2: finalColor = texture(textures[2], sampleCoords); break;
        case 3: finalColor = texture(textures[3], sampleCoords); break;
        case 4: finalColor = texture(textures[4], sampleCoords); break;
        case 5: finalColor = texture(textures[5], sampleCoords); break;
        case 6: finalColor = texture(textures[6], sampleCoords); break;
        case 7: finalColor = texture(textures[7], sampleCoords); break;
        case 8: finalColor = texture(textures[8], sampleCoords); break;
        case 9: finalColor = texture(textures[9], sampleCoords); break;
        case 10: finalColor = texture(textures[10], sampleCoords); break;
        case 11: finalColor = texture(textures[11], sampleCoords); break;
        case 12: finalColor = texture(textures[12], sampleCoords); break;
        case 13: finalColor = texture(textures[13], sampleCoords); break;
        case 14: finalColor = texture(textures[14], sampleCoords); break;
        case 15: finalColor = texture(textures[15], sampleCoords); break;
        case 16: finalColor = texture(textures[16], sampleCoords); break;
        case 17: finalColor = texture(textures[17], sampleCoords); break;
        case 18: finalColor = texture(textures[18], sampleCoords); break;
        case 19: finalColor = texture(textures[19], sampleCoords); break;
        case 20: finalColor = texture(textures[20], sampleCoords); break;
        case 21: finalColor = texture(textures[21], sampleCoords); break;
        case 22: finalColor = texture(textures[22], sampleCoords); break;
        case 23: finalColor = texture(textures[23], sampleCoords); break;
        case 24: finalColor = texture(textures[24], sampleCoords); break;
        case 25: finalColor = texture(textures[25], sampleCoords); break;
        case 26: finalColor = texture(textures[26], sampleCoords); break;
        case 27: finalColor = texture(textures[27], sampleCoords); break;
        case 28: finalColor = texture(textures[28], sampleCoords); break;
        case 29: finalColor = texture(textures[29], sampleCoords); break;
        case 30: finalColor = texture(textures[30], sampleCoords); break;
        case 31: finalColor = texture(textures[31], sampleCoords); break;
        default: finalColor = texture(textures[0], sampleCoords); break;
    };

    //finalColor = mix(finalColor, Color, finalColor.a);
    finalColor = finalColor * Color;
}
