#ifndef WINDOW_HANDLER_HPP
#define WINDOW_HANDLER_HPP

#include "OpenGlHeaders.hpp"
#include <string>

struct WindowHandler
{
   WindowHandler();
   ~WindowHandler();

   bool CreateWindow();
   bool CreateWindow(unsigned int w, unsigned int h, const std::string& n, unsigned int majV, unsigned int minV);

   void ProcessEscape();

   GLFWwindow* window;
   std::string  name;
   unsigned int width;
   unsigned int height;
   unsigned int majorVersion;
   unsigned int minorVersion;
};

#endif