#include "WindowHandler.hpp"
#include "Renderer.hpp"

#include <iostream>

WindowHandler::WindowHandler()
   :  window(),
      name("HI!"),
      width(800),
      height(600),
      majorVersion(4),
      minorVersion(6)
{
}

WindowHandler::~WindowHandler()
{}

bool WindowHandler::CreateWindow()
{
   if (!glfwInit())
   {
      return -1;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
   glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
   window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
   if (!window)
   {
      glfwTerminate();
      return -1;
   }

   glfwMakeContextCurrent(window);
   glfwSwapInterval(1);

   if(glewInit() != GLEW_OK)
   {
      std::cout << "Error Initializing GLEW!" << std::endl;
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

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   return true;
}

void WindowHandler::ProcessEscape()
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(window, true);
   }
}