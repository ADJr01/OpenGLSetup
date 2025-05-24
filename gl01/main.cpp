#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

const GLint WindowWidth = 1080, WindowHeight = 768;
bool set_gl_hints(int major_version,int minor_version,bool focus_on_show);
GLFWwindow* get_GLFW_Window(int width,int height,std::string title);

int main()
{
 
    std::string Title = "Graphical Window";
    int frame_buffer_width,frame_buffer_height;
    if (!glfwInit()) {
        std::cout << "Failed To Initialize GLFW\n";
        glfwTerminate();
        return 1;
    }
    //setup GLFW Properties
    set_gl_hints(3,3,true);
    GLFWwindow* Window = get_GLFW_Window(WindowWidth,WindowHeight,Title);
    if (!Window){
        std::cout << "Failed To Create GLFW Window\n";
        glfwTerminate();
        return 1;
    }
    glfwSetWindowAspectRatio(Window,16,9);
    glfwGetFramebufferSize(Window,&frame_buffer_width,&frame_buffer_height);
    glfwMakeContextCurrent(Window);
    glewExperimental=GL_TRUE;

    if(glewInit()!=GLEW_OK)
    {
        std::cout << "Failed To Initialize GLEW\n";
        glfwDestroyWindow(Window);
        glfwTerminate();
        return 1;
    }

    //setup
    glViewport(0,0,frame_buffer_width,frame_buffer_height);
    //create viewport tick
    while (!glfwWindowShouldClose(Window))
    {
        //handle user input
        glfwPollEvents();
        glClearColor(0.25f,0.66f,0.45f,0.88f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(Window);
    }
    glfwDestroyWindow(Window);
    glfwTerminate();
    
    return 0;
}

GLFWwindow* get_GLFW_Window(int width,int height,std::string title){
    return glfwCreateWindow(width,height,title.c_str(),NULL,NULL);
}

bool set_gl_hints(int major_version,int minor_version,bool focus_on_show){
    try
    {
        //responsible for setting up 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version); //3.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version); //3
        glfwWindowHint(GLFW_FOCUS_ON_SHOW,focus_on_show?GLFW_TRUE:GLFW_FALSE);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);
        return true;
    }catch (...)
    {
        std::cout << "Failed To Initialize OpenGL\n";
        return false;
    }
}