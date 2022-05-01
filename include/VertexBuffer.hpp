#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

struct VertexBuffer
{
   VertexBuffer(const void* data, unsigned int size);
   ~VertexBuffer();

   void Bind() const;
   void Unbind() const;

   unsigned int id;
};
#endif