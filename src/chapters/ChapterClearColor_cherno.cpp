#include "chapters/ChapterClearColor_cherno.hpp"

#include "Renderer.hpp"
#include "imgui/imgui.h"

namespace chapter
{
   ChapterClearColorCherno::ChapterClearColorCherno()
      : clearColor{0.2f, 0.3f, 0.3f, 1.0f}
   {}

   ChapterClearColorCherno::~ChapterClearColorCherno()
   {}

   void ChapterClearColorCherno::Update(float deltaTime)
   {}

   void ChapterClearColorCherno::Render()
   { 
      glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
      glClear(GL_COLOR_BUFFER_BIT);
   }

   void ChapterClearColorCherno::ImGuiRender()
   {
      ImGui::ColorEdit4("Clear Color", clearColor);
   }
}