#include "chapters/Chapter.hpp"

#include "imgui/imgui.h"

namespace chapter
{
   ChapterMenu::ChapterMenu(Chapter*& currentChapterPtr)
      : currentChapter(currentChapterPtr)
   {}

   ChapterMenu::~ChapterMenu()
   {}

   void ChapterMenu::ImGuiRender()
   {
      for (auto& chapter : chapters)
      {
         if (ImGui::Button(chapter.first.c_str()))
         {
            currentChapter = chapter.second();
         }

      }
   }
}