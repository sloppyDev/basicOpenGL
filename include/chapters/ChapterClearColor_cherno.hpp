#ifndef CHAPTER_CLEAR_COLOR_CHERNO_HPP
#define CHAPTER_CLEAR_COLOR_CHERNO_HPP

#include "Chapter.hpp"

namespace chapter
{
   struct ChapterClearColorCherno : Chapter
   {
      ChapterClearColorCherno();
      ~ChapterClearColorCherno();

      void Update(float deltaTime) override;
      void Render() override;
      void ImGuiRender() override;

      float clearColor[4];
   };
}
#endif