#include<iostream>
#include<memory>
#include "glx/Glx.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

GLuint VAO,vertexBufferID,shader;

std::string parseShader(const std::string& filepath,const std::string& startMarker,const std::string& endMarker);
void CreateTriangle();
void addShader(GLuint shader,const char* shader_code,GLenum shader_type);
void compileShader();

int main(){
    auto gl =std::make_unique<GLX>();
    gl->setVersionMajor(3);
    gl->setVersionMinor(3);
    gl->setAspectRatio(16,9);
    gl->setWindowWidth(static_cast<int>(gl->glx_primary_monitor_width()*0.5));
    gl->setWindowHeight(static_cast<int>(gl->glx_primary_monitor_height()*0.5));
    gl->setWindowTitle("GLX Window");
    gl->setIsForwardCompatable(true);
    gl->setFocusOnInit(true);
    gl->addPostLaunchProcedure(CreateTriangle);
    gl->addPostLaunchProcedure(compileShader);
    
    gl->onTick([=]()
    {
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
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
        };

        glGenVertexArrays(1,&VAO); //generating a vertex array that will hold vertex attribute configuration
        glBindVertexArray(VAO);// just saying hy GPU make it active for subsequent vertex attribute setup
        //creating buffer object
        glGenBuffers(1,&vertexBufferID); //creating Buffer Object to store vertex data
        glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);// Bind the VBO to the GL_ARRAY_BUFFER target for data upload
        glBufferData(GL_ARRAY_BUFFER,9*sizeof(GLfloat),vertices,GL_STATIC_DRAW);// Upload vertex data to the VBO. GL_STATIC_DRAW hints that the data is static
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*3,nullptr); // setting up VAO
        glEnableVertexAttribArray(0);// Enable vertex attribute 0 for use in rendering.

        //unbind VAO and vertexBufferID
        glBindBuffer(GL_ARRAY_BUFFER,0);// Unbind the VBO to prevent accidental modifications.
        glBindVertexArray(0);// Unbind the VAO to prevent accidental modifications.
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

void compileShader() {
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

std::string parseShader(const std::string& filepath,const std::string& startMarker,const std::string& endMarker) {
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filepath);
    }

    // Read entire file into a string
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    // Find the start marker
    size_t startPos = content.find(startMarker);
    if (startPos == std::string::npos) {
        // start marker not found
        return "";
    }
    // Move past the start marker
    startPos += startMarker.length();

    // Find the end marker after the start
    size_t endPos = content.find(endMarker, startPos);
    if (endPos == std::string::npos) {
        // If end marker not found, read until end of file
        endPos = content.length();
    }

    // Extract and return the substring
    return content.substr(startPos, endPos - startPos);
}