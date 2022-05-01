#include "OpenGlHeaders.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

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
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
   };

   unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
   };

   VertexArray va;
   VertexBuffer vb(vertices, 4*4*sizeof(float));
   VertexBufferLayout layout;
   layout.Push(GL_FLOAT, 2);
   layout.Push(GL_FLOAT, 2);
   va.AddBuffer(vb, layout);

   IndexBuffer ib(indices, 6);

   Shader shader("res/shaders/texture.glsl");
   shader.Bind();

   Texture texture("res/textures/beaker.jpg");
   texture.Bind();
   shader.SetUniform1i("u_texture", 0);

   va.Unbind();
   vb.Unbind();
   ib.Unbind();
   shader.Unbind();
   Renderer renderer;

   float r = 0.0f;
   float increment = 0.05f;
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   while (!glfwWindowShouldClose(window))
   {
      // Time Updates
      if (r > 1.0f || r < 0.0f)
      {
         increment *= -1;
      }
      r += increment;

      // Render
      renderer.StartRender(window);
      
      shader.Bind();
      renderer.Draw(va, ib, shader);

      renderer.FinishRender(window);
   }

   glfwTerminate();

   return 0;
}