
varying vec3 vBC;
attribute vec3 position, barycentric;
uniform mat4 proj, view;


void main(){
    vBC = barycentric;
    gl_Position = proj * view * vec4(position, 1.0);
}
