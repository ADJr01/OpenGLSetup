#include "GlxShader.h"

GlxShader::GlxShader(bool gl_context_status){
    if(!gl_context_status)return;
    shader = glCreateProgram();
    if(!shader)
    {
        std::cout<<"GLX Shader Processing Failed\n";
        return;
    }
    status=0;
    this->is_compiled=false;
    this->is_linked=false;
}
bool GlxShader::add_fragment_shader(std::string src){
    try
    {
        const auto shader_program = glCreateShader(GL_FRAGMENT_SHADER);
        ShadeObject shaderobj;
        shaderobj.src_string = static_cast<GLchar*>(malloc(sizeof(GLchar)*src.length()+1));
        shaderobj.src_ptr[0] = new char(src[0]);
        shaderobj.src_length[0] = static_cast<GLint>(src.length());
        shaderobj.program = shader_program;
        glShaderSource(shaderobj.program,1,shaderobj.src_ptr,shaderobj.src_length);
        this->fragment_shader=shaderobj;
        return true;
    }catch (...)
    {
        std::cout<<"Error while creating fragment shader\n";
        return false;
    }
    
}

bool GlxShader::add_vertex_shader(std::string src){
    try
    {
        const auto shader_program = glCreateShader(GL_VERTEX_SHADER);
        ShadeObject shaderobj;
        shaderobj.src_string = static_cast<GLchar*>(malloc(sizeof(GLchar)*src.length()+1));
        shaderobj.src_ptr[0] = new char(src[0]);
        shaderobj.src_length[0] = static_cast<GLint>(src.length());
        shaderobj.program = shader_program;
        glShaderSource(shaderobj.program,1,shaderobj.src_ptr,shaderobj.src_length);
        this->vertex_shader=shaderobj;
        return true;
    }catch (...)
    {
        std::cout<<"Error while creating vertex shader\n";
        return false;
    }
    
}

bool GlxShader::compile(){
    //compiling vertex shader
    bool compilation_face_1 = false;
    bool compilation_face_2 = false;
    glCompileShader(this->vertex_shader.program);
    glGetShaderiv(this->vertex_shader.program,GL_COMPILE_STATUS,&status);
    if (this->status == GL_FALSE || !this->status){
        std::cout<<"Error while compiling vertex shader\n";
        glGetShaderInfoLog(this->vertex_shader.program,1024,NULL,this->error_log);
        std::cout<<this->error_log<<"\n";
    }
    compilation_face_1 = this->status == GL_TRUE;
    if (!compilation_face_1)return compilation_face_1;
    glAttachShader(this->shader,this->vertex_shader.program);
    glCompileShader(this->fragment_shader.program);
    glGetShaderiv(this->fragment_shader.program,GL_COMPILE_STATUS,&status);
    if (this->status == GL_FALSE || !this->status)
    {
        std::cerr<<"GLX::Error while compiling fragment shader\n";
        glGetShaderInfoLog(this->fragment_shader.program,1024,NULL,this->error_log);
        std::cerr<<this->error_log<<"\n";
    }
    compilation_face_2 = this->status == GL_TRUE;
    if (!compilation_face_2)return false;
    glAttachShader(this->shader,this->fragment_shader.program);


    //linking process
    glLinkProgram(this->shader);
    glGetProgramiv(this->shader,GL_LINK_STATUS,&this->status);
    if (!this->status)
    {
        glGetProgramInfoLog(shader,1024,NULL,this->error_log);
        std::cerr<<"GLX::Failed to link shader"<<this->error_log<<"\n";
        return false;
    }

    //validate program
    glValidateProgram(this->shader);
    glGetProgramiv(this->shader,GL_VALIDATE_STATUS,&this->status);
    if (!this->status)
    {
        glGetProgramInfoLog(this->shader,1024,NULL,this->error_log);
        std::cerr<<"GLX::Shader Validation Error"<<this->error_log<<"\n";
        return false;
    }
    this->is_compiled=compilation_face_1 && compilation_face_2;
    this->is_compiled && std::cout<<"GLX::compiled successfully";
    return this->is_compiled;
}
GLuint GlxShader::get_shader_Instance(){
    if(this->is_compiled)return this->shader;
    return NULL;
}

GlxShader::~GlxShader(){
    glDeleteProgram(shader);
}
