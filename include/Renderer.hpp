#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "OpenGlHeaders.hpp"

#include <iostream>

struct VertexArray;
struct IndexBuffer;
struct Shader;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam);
void ProcessInput(GLFWwindow *window);

struct Renderer
{
   Renderer();
   ~Renderer();

   void StartRender(GLFWwindow* window);
   void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
   void FinishRender(GLFWwindow* window);
};

#endif