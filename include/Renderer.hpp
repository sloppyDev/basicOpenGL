#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "OpenGlHeaders.hpp"

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam);
void ProcessInput(GLFWwindow *window);

#endif