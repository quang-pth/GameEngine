#type vertex
#version 430 core

layout(location = 0) in vec3 aPosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
	gl_Position = projectionMatrix * viewMatrix * vec4(aPosition, 1.0);
}


#type fragment
#version 430 core

layout(location = 0) out vec4 finalColor;

uniform vec3 quadColor;

void main() {
	finalColor = vec4(quadColor, 1.0);
}
