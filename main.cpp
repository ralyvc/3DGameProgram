#define GLFW_DLL
#include "stdio.h"

#include "openGL/include/glad/glad.h"
#include "openGL/include/glfw/glfw3.h"


#include <iostream>
#include <stdlib.h>

// 注意 glad的引用一定要在GLFW之前
using namespace std;

void framebuffer_size_callback(GLFWwindow *window,int width,int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
    
    if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS  ) {
        glfwSetWindowShouldClose(window, true);
    }
    
}

void render(GLFWwindow *window)
{
    glClearColor(0.3, 0.1, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char const *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1024, 768, "OpenGL", NULL, NULL);

    
    if (window == NULL ) {
        std::cout << "Failed to Create GLFW Window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 1000, 800);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        render(window);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
