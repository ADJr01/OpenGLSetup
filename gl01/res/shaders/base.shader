#shader vertex
#version 410
layout (location = 0) in vec2 pos;
out vec3 vertexPositionData;

void main(){
    vertexPositionData= vec3(pos,1.0);
    gl_Position = vec4(pos,1.0,1.0);
}//$

#shader fragment
#version 410
out vec4 color;
in vec3 vertexPositionData;     
uniform float red;
uniform float green;
uniform float blue;
void main(){
    color = vec4(sin(red)/tan(vertexPositionData.x),(cos(green)*sin(vertexPositionData.y)),sin(blue),1.0);  

}//fragEnd