#include "vzpch.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>

namespace vz
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear(ClearFlag flags)
	{
		GLbitfield clearFlags = 0;

		uint8_t calcFlag = SCAST(uint8_t, flags);

		while(calcFlag)
		{

			if ((calcFlag ^ STENCIL) < calcFlag)
			{
				calcFlag -= STENCIL;
				clearFlags |= GL_STENCIL_BUFFER_BIT;

				if (!calcFlag)
					break;
			}

			if ((calcFlag ^ DEPTH) < calcFlag)
			{
				calcFlag -= DEPTH;
				clearFlags |= GL_DEPTH_BUFFER_BIT;

				if (!calcFlag)
					break;
			}

			if ((calcFlag ^ COLOR) < calcFlag)
			{
				calcFlag -= COLOR;
				clearFlags |= GL_COLOR_BUFFER_BIT;

				if (!calcFlag)
					break;
			}
		}

		glClear(clearFlags);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<IVertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, CVOID(0));
	}
}
