#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
   std::string VertexSource;
   std::string FragmentSource;
};

struct Shader
{
   Shader(const std::string& name);
   ~Shader();

   void Bind() const;
   void Unbind() const;

   void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

   int GetUniformLocation(const std::string& name);

   ShaderProgramSource ParseShader(const std::string& path);
   unsigned int CompileShader(unsigned int type, const std::string& source);
   unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

   unsigned int id;
   std::string filePath;
   std::unordered_map<std::string, int> locationCache;

};
#endif