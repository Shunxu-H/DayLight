#version 130
#extension GL_OES_standard_derivatives : enable


varying vec3 vBC;
//out vec4 outColor;

float edgeFactor(){
    vec3 d = fwidth(vBC);
    vec3 a3 = smoothstep(vec3(0.0), d*0.95, vBC);
    return min(min(a3.x, a3.y), a3.z);
}


void main(){
    //outColor = vec4( 1, 1, 1, 1);
    gl_FragColor = mix(vec4(1.0, 1.0, 1.0, 1.0), vec4(0.0), edgeFactor());
    //gl_FragColor.a = (1.0-edgeFactor())*0.95;

    //gl_FragColor = vec4(0.0, 0.0, 0.0, (1.0-edgeFactor())*0.95);
}
