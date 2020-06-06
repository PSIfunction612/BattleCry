//
// Created by shala on 28.05.2020.
//

#ifndef BATTLECRY_SHADERPROGRAM_H
#define BATTLECRY_SHADERPROGRAM_H
#include <glad/glad.h>

#include <string>
#include <glm/mat4x4.hpp>

namespace Renderer{
    class ShaderProgram{
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ~ShaderProgram();
        bool isCompiled() const {return m_isCompiled;}
        void use() const;
        void setInt(const std::string& name, const GLint value);
        void setMatrix4(const std::string& name, const glm::mat4 matrix);

        ShaderProgram(const ShaderProgram & program) = delete;
        ShaderProgram& operator=(const ShaderProgram& program) = delete;
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
    private:
        bool createShader(const std::string& shader, const GLenum shaderType, GLuint& shaderID);
        bool m_isCompiled = false;
        GLuint m_ID = 0;
    };

}

#endif //BATTLECRY_SHADERPROGRAM_H
