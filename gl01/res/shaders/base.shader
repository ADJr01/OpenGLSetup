#shader vertex
#version 410
layout (location = 0) in vec3 pos;
out vec4 vertexColor;

void main(){
    vertexColor=vec4(pos,1.0);
    gl_Position = vec4(pos,1.0);
}//$

#shader fragment
#version 410
out vec4 color;
in vec4 vertexColor;     
uniform float red;
uniform float green;
uniform float blue;
void main(){
    //color = vertexColor;
      color = vec4(red,green,blue,1.0);  

}//fragEnd