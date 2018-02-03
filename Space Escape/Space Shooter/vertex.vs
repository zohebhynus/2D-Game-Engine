#version 330
layout (location = 0)in vec3 position;
layout (location = 1)in vec3 color;

uniform mat4 transform;
uniform mat4 scale;

out vec3 ourColor;

void main(){

	gl_Position =  transform * vec4(position.x, position.y, position.z, 1.0f);

	ourColor = color;

}