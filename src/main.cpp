#include "OpenGlHeaders.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

#include <iostream>

#define DEBUG

int main()
{
   GLFWwindow* window;

   if (!glfwInit())
   {
      return -1;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
   glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
   window = glfwCreateWindow(800, 600, "Basic OpenGL", NULL, NULL);
   if (!window)
   {
      glfwTerminate();
      return -1;
   }

   glfwMakeContextCurrent(window);
   glfwSwapInterval(1);

   if(glewInit() != GLEW_OK)
   {
      std::cout << "Error!" << std::endl;
   }
   std::cout << glGetString(GL_VERSION) << std::endl;

#ifdef DEBUG
   int flags;
   glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
   if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
   {
      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(glDebugOutput, nullptr);
      glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
   }
#endif

   glViewport(0, 0, 800, 600);
   glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

   // Define Vertex Buffer
   float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
   };

   unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
   };

   unsigned int vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   VertexArray va;
   VertexBuffer vb(vertices, 4*2*sizeof(float));
   VertexBufferLayout layout;
   layout.Push(GL_FLOAT, 2);
   va.AddBuffer(vb, layout);

   IndexBuffer ib(indices, 6);

   Shader shader("res/shaders/basic.glsl");
   shader.Bind();
   shader.SetUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);

   va.Unbind();
   vb.Unbind();
   ib.Unbind();
   shader.Unbind();

   float r = 0.0f;
   float increment = 0.05f;
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   while (!glfwWindowShouldClose(window))
   {
      // Inputs
      ProcessInput(window);

      // Time Updates
      if (r > 1.0f || r < 0.0f)
      {
         increment *= -1;
      }
      r += increment;

      // Render
      glClear(GL_COLOR_BUFFER_BIT);

      va.Bind();
      vb.Bind();
      ib.Bind();
      shader.Bind();
      shader.SetUniform4f("u_color", r, 0.3f, 0.8f, 1.0f);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

      // Swap front and back buffers
      glfwSwapBuffers(window);

      // Poll for window events
      glfwPollEvents();
   }

   glfwTerminate();

   return 0;
}