#version 130


uniform vec3 pickingColor;

out vec4 finalColor;

void main() {
    //set every drawn pixel to white
    finalColor = vec4(pickingColor, 1);
}
