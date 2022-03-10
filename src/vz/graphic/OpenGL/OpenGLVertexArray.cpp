#include "vzpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace vz
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_id);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_id);

		// Delete raw pointer of vertex buffer and index buffer
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_id);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<IVertexBuffer>& buffer, int bindIndex)
	{
		// Asserting to prevent setting non-layout VertexBuffer
		VZ_CORE_ASSERT(buffer->GetLayout().GetElements().size(), "Buffer has no layout implemented!");

		// Setting layout
		int index = 0;
		for (auto& element : buffer->GetLayout())
		{
			glEnableVertexArrayAttrib(m_id, index);
			glVertexArrayAttribFormat(m_id, bindIndex, GetCountOfShaderType(element.Type), GL_FLOAT,
				VZ_SHORT_IF(element.Normalized, GL_TRUE, GL_FALSE), element.Offset);
			++index;
		}

		// Set Vertex Buffer
		glVertexArrayVertexBuffer(m_id, bindIndex, buffer->Get(), 0, buffer->GetLayout().GetStride());

		// Take reference
		m_vertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IIndexBuffer>& buffer)
	{
		glVertexArrayElementBuffer(m_id, buffer->Get());

		// Take reference
		m_indexBuffer = buffer;
	}

	const std::vector<std::shared_ptr<IVertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_vertexBuffers;
	}

	const std::shared_ptr<IIndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_indexBuffer;
	}
}
