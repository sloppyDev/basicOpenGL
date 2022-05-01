#include "Shader.hpp"

#include "Renderer.hpp"

#include <fstream>
#include <sstream>

Shader::Shader(const std::string& name)
   : filePath(name),
     id(0)
{
   ShaderProgramSource source = ParseShader(filePath);
   id = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
   glDeleteProgram(id);
}

void Shader::Bind() const
{
   glUseProgram(id);
}

void Shader::Unbind() const
{
   glUseProgram(0);
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
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

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
   unsigned int ID = glCreateShader(type);
   const char* src = source.c_str();
   glShaderSource(ID, 1, &src, nullptr);
   glCompileShader(ID);

   int result;
   glGetShaderiv(ID, GL_COMPILE_STATUS, &result);
   if (result == GL_FALSE)
   {
      int length;
      glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length);
      char* message = (char*) alloca(length*sizeof(char));
      glGetShaderInfoLog(ID, length, &length, message);

      std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
      std::cout << message << std::endl;

      glDeleteShader(ID);
      return 0;
   }

   return ID; 
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
   glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

int Shader::GetUniformLocation(const std::string& name)
{
   if (locationCache.find(name) != locationCache.end())
   {
      return locationCache[name];
   }
   else
   {
      int location = glGetUniformLocation(id, name.c_str());
      locationCache[name] = location;

      if (location == -1)
      {
         std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
      }

      return location;
   }
}