#ifndef CHAPTER_HPP
#define CHAPTER_HPP

#include <functional>
#include <string>
#include <iostream>
#include <vector>

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

   struct ChapterMenu : Chapter
   {
      ChapterMenu(Chapter*& currentChapterPtr);
      ~ChapterMenu();

      void ImGuiRender() override;

      template<typename T>
      void RegisterChapter(const std::string& name)
      {
         std::cout << "Registering Chapter: " << name << std::endl;
         chapters.push_back(std::make_pair(name, []() {return new T(); }));
      }

      Chapter*& currentChapter;
      std::vector<std::pair<std::string, std::function<Chapter*()>>> chapters;
   };
}
#endif

