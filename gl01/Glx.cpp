#include "Glx.h"
#include <iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<functional>
#include<vector>

GLX::GLX(){
    this->window = nullptr;
    this->is_running=false;
    this->open_gl_version_major=3;
    this->open_gl_version_minor=3;
    this->Window_Width=800;
    this->Window_Height=600;
    this->focus_on_init=false;
    this->is_forward_compatable=false;
    this->WindowAspectRatio.numerator=16;
    this->WindowAspectRatio.denumerator=9;
    this->gl_experimental=true;
}

void GLX::setVersionMajor(int version_major){
    this->open_gl_version_major=version_major;
}

void GLX::setGLExperimental(bool experimental){
    this->gl_experimental=experimental;
}

void GLX::setVersionMinor(int version_minor){
    this->open_gl_version_minor=version_minor;
}
void GLX::setFocusOnInit(bool focus_on_init){
    this->focus_on_init=focus_on_init;
}
void GLX::setWindowWidth(int window_width){
    this->Window_Width=window_width;
}
void GLX::setWindowHeight(int window_height){
    this->Window_Height=window_height;
}
void GLX::setWindowTitle(std::string window_title){
    this->Window_title=window_title;
}
void GLX::setIsForwardCompatable(bool is_forward_compatable){
    this->is_forward_compatable=is_forward_compatable;
}
void GLX::setAspectRatio(int nume, int denume){
    this->WindowAspectRatio.numerator = nume;
    this->WindowAspectRatio.denumerator = denume;
}

template<typename Func, typename... Args>
   void  GLX::onTick(Func func, Args... args) {
   this->tasklist.push_back(std::bind(func, args...));
}

bool GLX::launch(){
    try
    {
    if (!glfwInit()) {
        std::cout << "Failed To Init GLX:: Error occured when initializing glfw.";
        glfwTerminate();
    }
        //responsible for setting up 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->open_gl_version_major); //3.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->open_gl_version_minor); //3
        glfwWindowHint(GLFW_FOCUS_ON_SHOW,this->focus_on_init?GLFW_TRUE:GLFW_FALSE);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,this->is_forward_compatable?GLFW_TRUE:GLFW_FALSE);
        //create GLFW Window
        this->window = glfwCreateWindow(this->Window_Width,this->Window_Height,this->Window_title.c_str(),NULL,NULL);
        if (!this->window)
        {
            std::cout << "Failed To Init GLX:: Error occured when initializing Window.\n";
            glfwTerminate();
            return false;
        }
        glfwSetWindowAspectRatio(this->window,this->WindowAspectRatio.numerator,this->WindowAspectRatio.denumerator);
        glfwGetFramebufferSize(this->window,&this->frame_buffer_width,&this->frame_buffer_height);
        glfwMakeContextCurrent(this->window);
        glewExperimental=this->gl_experimental?GL_TRUE:GL_FALSE;
        
        return true;
    }catch (...)
    {
        glfwTerminate();
        std::cout << "Failed To launch GLX.\n";
        return false;
    }
}

