#include "axpch.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

// TODO: implement this :D

namespace Apex {

    Shader::Shader(std::string& vertexSrc, std::string& fragmentSrc)
    {
	}

	Shader::~Shader()
	{
		//glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		//glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		//glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		//GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		//glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}