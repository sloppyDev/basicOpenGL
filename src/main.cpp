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

   chapter::ChapterClearColorCherno chapter;

/*
   // Define Vertex Buffer
   float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
   };

   unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
   };

   VertexArray va;
   VertexBuffer vb(vertices, 4*4*sizeof(float));
   VertexBufferLayout layout;
   layout.Push(GL_FLOAT, 2);
   layout.Push(GL_FLOAT, 2);
   va.AddBuffer(vb, layout);

   IndexBuffer ib(indices, 6);

   Shader shader("res/shaders/texture.glsl");
   shader.Bind();

   Texture texture("res/textures/beaker.jpg");
   texture.Bind();
   shader.SetUniform1i("u_texture", 0);

   va.Unbind();
   vb.Unbind();
   ib.Unbind();
   shader.Unbind();

   float r = 0.0f;
   float increment = 0.05f;
   */
   float clearColor[4] = {0.2f, 0.3f, 0.3f, 1.0f};
   glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
   while (!glfwWindowShouldClose(windowHandler.window))
   {
      windowHandler.ProcessEscape();
      glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
/*
      // Time Updates
      if (r > 1.0f || r < 0.0f)
      {
         increment *= -1;
      }
      r += increment;
*/
      // Render
      renderer.StartRender(windowHandler.window);

      chapter.Update(0.0f);
      chapter.Render();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
/*      
      shader.Bind();
      renderer.Draw(va, ib, shader);

      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color

      if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
*/
      chapter.ImGuiRender();
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      renderer.FinishRender(windowHandler.window);
   }

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
   glfwTerminate();

   return 0;
}