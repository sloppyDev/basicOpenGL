#include "VertexArray.hpp"

VertexArray::VertexArray()
{
   glGenVertexArrays(1, &id);
   Bind();
}
VertexArray::~VertexArray()
{
   glDeleteVertexArrays(1, &id);
}

void VertexArray::Bind() const
{
   glBindVertexArray(id);
}

void VertexArray::Unbind() const
{
   glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
   Bind();
   vb.Bind();
   const auto& elements = layout.GetElements();
   int offset = 0;
   for (unsigned int i = 0; i < elements.size(); i++)
   {
      const auto& element = elements[i];
      glEnableVertexAttribArray(i);
      glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(intptr_t) offset);
      offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
   }
}