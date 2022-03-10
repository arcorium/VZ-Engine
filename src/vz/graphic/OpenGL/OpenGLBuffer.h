#pragma once
#include "vz/graphic/Buffer.h"

namespace vz
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned size, const void* data);

		~OpenGLVertexBuffer() override;

		void SetData(unsigned size, const void* data) override;
		void SetSubData(unsigned size, unsigned offset, const void* data) override;
		inline void SetStorage(unsigned size, const void* data) override;

		void SetLayout(const BufferLayout& layout) override;
		const BufferLayout& GetLayout() const override;

		unsigned GetSize() const override;

	private:
		unsigned m_size;
		BufferLayout m_layout;
	};

	class OpenGLIndexBuffer : public IIndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned size, const void* data);
		~OpenGLIndexBuffer() override;

		void SetData(unsigned size, const void* data) override;
		void SetSubData(unsigned size, unsigned offset, const void* data) override;
		
		inline void SetStorage(unsigned size, const void* data) override;

		int GetCount() const override;

	private:
		uint32_t m_count;
	};
}
