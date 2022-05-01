#ifndef VERTEX_BUFFER_LAYOUT_HPP
#define VERTEX_BUFFER_LAYOUT_HPP

#include "OpenGlHeaders.hpp"
#include <vector>

struct VertexBufferElement
{
   unsigned int type;
   unsigned int count;
   unsigned char normalized;

   static unsigned int GetSizeOfType(unsigned int type)
   {
      switch (type)
      {
         case GL_FLOAT:         return 4;
         case GL_UNSIGNED_INT:  return 4;
         case GL_UNSIGNED_BYTE: return 1;
      }
      return 0;
   }
};

struct VertexBufferLayout
{
   VertexBufferLayout()
      :stride(0) {}

   std::vector<VertexBufferElement> elements;
   unsigned int stride;

   inline void Push(unsigned int type, unsigned int count, unsigned char normalized=GL_FALSE)
   {
      elements.push_back({type, count, normalized});
      stride += count*VertexBufferElement::GetSizeOfType(type);
   }
   inline const std::vector<VertexBufferElement> GetElements() const {return elements;};
   inline unsigned int GetStride() const {return stride;};
};
#endif