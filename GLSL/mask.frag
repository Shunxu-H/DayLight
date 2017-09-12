#version 130

out vec4 finalColor;

uniform vec4 diffuseColor;

void main() {
    //set every drawn pixel to white
    finalColor = diffuseColor;
}
