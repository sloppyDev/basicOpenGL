#include "OpenGlHeaders.hpp"
#include "OpenGlUtilityFunctions.cpp"

#include <iostream>
#include <fstream>
#include <sstream>

#define DEBUG

struct ShaderProgramSource
{
   std::string VertexSource;
   std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
   std::ifstream stream(filePath);

   enum class ShaderType
   {
      NONE = -1,
      VERTEX = 0,
      FRAGMENT = 1
   };

   std::string line;
   std::stringstream ss[2];
   ShaderType type = ShaderType::NONE;
   while (getline(stream, line))
   {
      if (line.find("#shader") != std::string::npos)
      {
         if (line.find("vertex") != std::string::npos)
         {
            type = ShaderType::VERTEX;
         }
         else if (line.find("fragment") != std::string::npos)
         {
            type = ShaderType::FRAGMENT;
         }
      }
      else
      {
         ss[(int)type] << line << "\n";
      }
   }

   return {ss[0].str(), ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
   unsigned int id = glCreateShader(type);
   const char* src = source.c_str();
   glShaderSource(id, 1, &src, nullptr);
   glCompileShader(id);

   int result;
   glGetShaderiv(id, GL_COMPILE_STATUS, &result);
   if (result == GL_FALSE)
   {
      int length;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
      char* message = (char*) alloca(length*sizeof(char));
      glGetShaderInfoLog(id, length, &length, message);

      std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
      std::cout << message << std::endl;

      glDeleteShader(id);
      return 0;
   }

   return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
   unsigned int program = glCreateProgram();
   unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
   unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

   glAttachShader(program, vs);
   glAttachShader(program, fs);
   glLinkProgram(program);
   glValidateProgram(program);
   
   glDeleteShader(vs);
   glDeleteShader(fs);

   return program;
}

int main()
{
   GLFWwindow* window;

   if (!glfwInit())
   {
      return -1;
   }

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef DEBUG
   glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
   window = glfwCreateWindow(800, 600, "Basic OpenGL", NULL, NULL);
   if (!window)
   {
      glfwTerminate();
      return -1;
   }

   glfwMakeContextCurrent(window);
   glfwSwapInterval(1);

   if(glewInit() != GLEW_OK)
   {
      std::cout << "Error!" << std::endl;
   }
   std::cout << glGetString(GL_VERSION) << std::endl;

#ifdef DEBUG
   int flags;
   glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
   if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
   {
      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(glDebugOutput, nullptr);
      glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
   }
#endif

   glViewport(0, 0, 800, 600);
   glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

   // Define Vertex Buffer
   float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
   };

   unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
   };

   unsigned int vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   unsigned int buffer;
   glGenBuffers(1, &buffer);
   glBindBuffer(GL_ARRAY_BUFFER, buffer);
   glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), vertices, GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

   unsigned int ibo;
   glGenBuffers(1, &ibo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW);

   ShaderProgramSource source = ParseShader("res/shaders/basic.glsl");
   unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
   glUseProgram(shader);

   int location = glGetUniformLocation(shader, "u_color");
   glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f);

   float r = 0.0f;
   float increment = 0.05f;
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   while (!glfwWindowShouldClose(window))
   {
      // Inputs
      ProcessInput(window);

      // Time Updates
      if (r > 1.0f || r < 0.0f)
      {
         increment *= -1;
      }
      r += increment;

      // Render
      glClear(GL_COLOR_BUFFER_BIT);

      glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

      // Swap front and back buffers
      glfwSwapBuffers(window);

      // Poll for window events
      glfwPollEvents();
   }

   glfwTerminate();
   glDeleteProgram(shader);

   return 0;
}