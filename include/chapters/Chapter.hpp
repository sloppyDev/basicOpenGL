#ifndef CHAPTER_HPP
#define CHAPTER_HPP

namespace chapter
{
   struct Chapter
   {
      Chapter() {}
      virtual ~Chapter() {}

      virtual void Update(float deltaTime) {}
      virtual void Render() {}
      virtual void ImGuiRender() {}
   };
}
#endif

