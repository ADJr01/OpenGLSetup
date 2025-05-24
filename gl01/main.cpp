#include<iostream>
#include "Glx.h"


int main(){
    GLX gl;
    gl.setAspectRatio(16,9);
    gl.setWindowTitle("Test Window");
    gl.setIsForwardCompatable(true);
    gl.setFocusOnInit(true);
    gl.launch();
    
}

