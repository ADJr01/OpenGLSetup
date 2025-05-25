#ifndef __GLX_SHADER_H__
#define __GLX_SHADER_H__
#include <iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

struct ShadeObject{
    GLuint program;
    std::string src_string;
    GLchar*  src_ptr[1];
    GLint src_length[1];
};
class GlxShader{
private:
    bool is_compiled,is_linked;
    GLuint shader;
    ShadeObject vertex_shader;
    ShadeObject fragment_shader;
    GLint status;
    GLchar error_log[1024];
    public:
    GlxShader(bool gl_context_status);
    ~GlxShader();
    bool add_fragment_shader(std::string source);
    bool add_vertex_shader(std::string source);
    bool compile();
    GLuint get_shader_Instance();
    
    
};

#endif