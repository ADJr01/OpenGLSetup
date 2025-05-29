#shader vertex
#version 410
layout (location = 0) in vec4 pos;

void main(){
    gl_Position = pos;

};

#shader fragment
#version 410
out vec4 color;
uniform float u_time;       // Time in seconds since load
void main(){
    color = vec4(abs(sin(u_time*10)),0.0,0.0,1.0);;

}