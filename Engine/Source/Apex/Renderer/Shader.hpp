#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Apex
{
    class Shader
    {
    public:
        Shader(std::string& vertexSrc, std::string& fragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    private:
        uint32_t m_RendererID;
    };
    
}