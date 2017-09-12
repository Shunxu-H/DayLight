#version 130
#extension GL_OES_standard_derivatives : enable


varying vec3 vBC;


float edgeFactor(){
    vec3 d = fwidth(vBC);
    vec3 a3 = smoothstep(vec3(0.0), d*0.95, vBC);
    return min(min(a3.x, a3.y), a3.z);
}

void main(){
    gl_FragColor.rgb = mix(vec3(0.0), vec3(0.5), edgeFactor());
    gl_FragColor.a = 1.0;
}
