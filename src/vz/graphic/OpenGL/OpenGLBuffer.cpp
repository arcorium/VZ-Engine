#include "vzpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace vz
{
	/** ************************************************************************************************ **/
	/** ***********************************  VertexBuffer  ********************************************* **/
	/** ************************************************************************************************ **/

	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned size, const void* data)
		: m_size(0), m_layout()
	{
		glCreateBuffers(1, &m_id);
		SetData(size, data);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void OpenGLVertexBuffer::SetData(unsigned size, const void* data)
	{
		glNamedBufferData(m_id, size, data, GL_STATIC_DRAW);

		m_size = size;
	}

	void OpenGLVertexBuffer::SetSubData(unsigned size, unsigned offset, const void* data)
	{
		glNamedBufferSubData(m_id, offset, size, data);
	}

	void OpenGLVertexBuffer::SetStorage(unsigned size, const void* data)
	{
		glNamedBufferStorage(m_id, size, data, GL_DYNAMIC_STORAGE_BIT);

		m_size = size;
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_layout = layout;
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_layout;
	}

	unsigned OpenGLVertexBuffer::GetSize() const
	{
		return m_size;
	}

	/** ************************************************************************************************ **/
	/** ************************************  IndexBuffer  ********************************************* **/
	/** ************************************************************************************************ **/

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned size, const void* data)
		: m_count(0)
	{
		glCreateBuffers(1, &m_id);
		SetData(size, data);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void OpenGLIndexBuffer::SetData(unsigned size, const void* data)
	{
		glNamedBufferData(m_id, size, data, GL_STATIC_DRAW);

		m_count = size / sizeof(uint32_t);
	}

	void OpenGLIndexBuffer::SetSubData(unsigned size, unsigned offset, const void* data)
	{
		glNamedBufferSubData(m_id, offset, size, data);
	}

	void OpenGLIndexBuffer::SetStorage(unsigned size, const void* data)
	{
		glNamedBufferStorage(m_id, size, data, GL_DYNAMIC_STORAGE_BIT);

		m_count = size / sizeof(uint32_t);
	}

	int OpenGLIndexBuffer::GetCount() const
	{
		return m_count;
	}
}
