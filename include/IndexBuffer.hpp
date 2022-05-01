#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

struct IndexBuffer
{
   IndexBuffer(const unsigned int* data, unsigned int cnt);
   ~IndexBuffer();

   void Bind() const;
   void Unbind() const;

   unsigned int id;
   unsigned int count;
};
#endif