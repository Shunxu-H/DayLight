#version 330


uniform vec3 pickingColor;

layout (location = 0) out vec4 finalColor;

void main() {
    //set every drawn pixel to white
    finalColor = vec4(pickingColor, 1);
}
