#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

struct VertexArray
{
   VertexArray();
   ~VertexArray();

   void Bind() const;
   void Unbind() const;

   void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

   unsigned int id;
};
#endif