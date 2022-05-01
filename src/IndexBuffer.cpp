#include "IndexBuffer.hpp"

#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int cnt)
   : count(cnt)
{
   glGenBuffers(1, &id);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
   glDeleteBuffers(1, &id);
}

void IndexBuffer::Bind() const
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::Unbind() const
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}