#ifndef GLX_H
#define GLX_H
#include <string>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<functional>
#include<vector>

struct Ratio{
    int numerator;
    int denumerator;
};
class GLX{
private:
    GLFWwindow* window;
    Ratio WindowAspectRatio;
    bool is_running;
    bool gl_experimental;
    std::string Window_title;
    int open_gl_version_minor;
    int open_gl_version_major;
    bool focus_on_init;
    bool is_forward_compatable;
    int Window_Width, Window_Height, frame_buffer_width, frame_buffer_height;
    std::vector<std::function<void()>> tasklist;
    void destroy();
    public:
    GLX();
    ~GLX();
    void setAspectRatio(int nume, int denume);
    void setGLExperimental(bool experimental);
    void setVersionMajor(int ver_major);
    void setVersionMinor(int ver_minor);
    void setFocusOnInit(bool focus_on_init);
    void setWindowHeight(int window_height);
    void setWindowWidth(int window_width);
    void setWindowTitle(std::string window_title);
    void setIsForwardCompatable(bool is_forward_compatable);
    template<typename Func, typename... Args>
    void onTick(Func func, Args... args);
    bool launch();
    
};

#endif