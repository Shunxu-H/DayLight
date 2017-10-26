#version 130
varying vec3 vBC;
attribute vec3 vert;
uniform mat4 camera;
uniform mat4 model;
uniform mat4 projection;



void main(){
    if ( (gl_VertexID % 3) == 0)
        vBC = vec3(1.0, 0.0, 0.0);
    else if ( (gl_VertexID % 3) == 1)
        vBC = vec3(0.0, 1.0, 0.0 );
    else
        vBC = vec3(0.0, 0.0, 1.0 );
    gl_Position = projection * camera * model * vec4(vert, 1.0);
}
