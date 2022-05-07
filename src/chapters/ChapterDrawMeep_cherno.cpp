/*
#include "chapters/ChapterDrawMeep_cherno.hpp"

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace chapter
{
   ChapterDrawMeepCherno::ChapterDrawMeepCherno()
   {
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
   }

   ChapterDrawMeepCherno::~ChapterDrawMeepCherno()
   {}

   void ChapterDrawMeepCherno::Update(float deltaTime)
   {}

   void ChapterDrawMeepCherno::Render()
   {}

   void ChapterDrawMeepCherno::ImGuiRender()
   {}
}
*/