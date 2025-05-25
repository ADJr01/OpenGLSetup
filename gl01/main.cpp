#include<iostream>
#include<memory>
#include "Glx.h"

GLuint VAO,VBO,shader;

const auto vertex_shader = R"(
#version 410
layout (location = 0) in vec3 pos;

void main(){
    gl_Position = vec4(pos.x*0.2, pos.y*0.2, pos.z*0.2, 1.0);

})";

const auto fragment_shader = R"(
#version 410
out vec4 color;

void main(){
      color = vec4(1,1.0,1.0,1.0);

})";

void CreateTriangle();
void addShader(GLuint shader,const char* shader_code,GLenum shader_type);
void compileShader();

int main(){
    auto gl =std::make_unique<GLX>();
    gl->setVersionMajor(3);
    gl->setVersionMinor(3);
    gl->setAspectRatio(16,9);
    gl->setWindowWidth(1366);
    gl->setWindowHeight(768);
    gl->setWindowTitle("GLX Window");
    gl->setIsForwardCompatable(true);
    gl->setFocusOnInit(true);
    gl->addPostLaunchProcedure(CreateTriangle);
    gl->addPostLaunchProcedure(compileShader);
    
    gl->onTick([=]()
    {
        glClearColor(0.0f,0.0f,0.0f,1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        glUseProgram(0);
        glBindVertexArray(0);

    });

    gl->launch();
    gl->inf();
    return 0;
    
}


void CreateTriangle(){
    try
    {
        GLfloat vertices[] =   {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glGenVertexArrays(1,&VAO); //generating a vertex array that will hold vertex Buffers. Mainly vertex data
        glBindVertexArray(VAO);// just saying hy GPU, take this vertex array object.
        //creating buffer object
        glGenBuffers(1,&VBO); //creating Buffer Object to store vertex data
        glBindBuffer(GL_ARRAY_BUFFER,VBO);// saying GPU I want to work with this specific buffer for a specific purpose.
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);
        glEnableVertexAttribArray(0);

        //unbind VAO and VBO
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
        std::cout<<"Triangle Defined successfully"<<std::endl;
    }catch(...)
    {
        std::cout<<"Error creating triangle"<<glGetError()<<std::endl;
        return;
    }

}
void addShader(GLuint shader,const char* shader_code,GLenum shader_type){
    auto shader_program = glCreateShader(shader_type);
    const GLchar* shader_src[1];
    shader_src[0] = shader_code;
    GLint code_length[1];
    code_length[0] = static_cast<GLint>(strlen(shader_src[0]));
    glShaderSource(shader_program,1,shader_src,code_length);
    glCompileShader(shader_program);
    GLint result = 0;
    GLchar infoLog[512] = {0};
    glGetShaderiv(shader_program,GL_COMPILE_STATUS,&result);
    if (!result)
    {
        glGetShaderInfoLog(shader_program,1024,NULL,infoLog);
        std::cout<<"Failed to compile shader of type "<<shader_type<<" "<<infoLog<<std::endl;
        return;
    }
    glAttachShader(shader,shader_program);
    return;
}

void compileShader(){
    shader = glCreateProgram();
    if (!shader)
    {
        std::cout<<"Failed to create shader"<<std::endl;
        return;
    }
    addShader(shader,vertex_shader,GL_VERTEX_SHADER);
    addShader(shader,fragment_shader,GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar infoLog[1024] = {0};
    glLinkProgram(shader);
    glGetProgramiv(shader,GL_LINK_STATUS,&result);
    if (!result)
    {
        glGetProgramInfoLog(shader,1024,NULL,infoLog);
        std::cout<<"Failed to link shader"<<infoLog<<std::endl;
        return;
    }

    //validate program
    glValidateProgram(shader);
    glGetProgramiv(shader,GL_VALIDATE_STATUS,&result);
    if (!result)
    {
        glGetProgramInfoLog(shader,1024,NULL,infoLog);
        std::cout<<"Failed to validating shader"<<infoLog<<std::endl;
        return;
    }
    std::cout<<"Shader compiled successfully"<<std::endl;
}