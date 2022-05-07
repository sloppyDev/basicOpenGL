#define DEBUG

#include "OpenGlHeaders.hpp"
#include "WindowHandler.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "chapters/ChapterClearColor_cherno.hpp"

int main()
{
   WindowHandler windowHandler;
   windowHandler.CreateWindow();

   ImGui::CreateContext();
   ImGui_ImplGlfw_InitForOpenGL(windowHandler.window, true);
   ImGui_ImplOpenGL3_Init("#version 130");
   ImGui::StyleColorsDark();

   Renderer renderer;

   chapter::Chapter* currentChapter = nullptr;
   chapter::ChapterMenu* chapterMenu = new chapter::ChapterMenu(currentChapter);
   currentChapter = chapterMenu;

   chapterMenu->RegisterChapter<chapter::ChapterClearColorCherno>("Clear Color");

   float clearColor[4] = {0.2f, 0.3f, 0.3f, 1.0f};
   while (!glfwWindowShouldClose(windowHandler.window))
   {
      glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
      glClear(GL_COLOR_BUFFER_BIT);
      windowHandler.ProcessEscape();

      // Render
      renderer.StartRender(windowHandler.window);

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      if (currentChapter)
      {
         currentChapter->Update(0.0f);
         currentChapter->Render();
         ImGui::Begin("Chapter");

         if (currentChapter != chapterMenu && ImGui::Button("<-"))
         {
            currentChapter = chapterMenu;
         }
         currentChapter->ImGuiRender();
         ImGui::End();
      }

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      renderer.FinishRender(windowHandler.window);
   }

   delete currentChapter;
   if (currentChapter != chapterMenu)
   {
      delete chapterMenu;
   }

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
   glfwTerminate();

   return 0;
}