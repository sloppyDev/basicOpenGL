#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Renderer.hpp"

struct Texture
{
   Texture(const std::string& path);
   ~Texture();

   void Bind(unsigned int slot=0) const;
   void Unbind() const;

   unsigned int id;
   std::string filePath;
   unsigned char* localBuffer;
   int width;
   int height;
   int bpp;
};
#endif