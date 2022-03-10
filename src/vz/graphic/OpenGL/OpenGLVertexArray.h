#pragma once
#include "../VertexArray.h"

namespace vz
{
	class VZ_API OpenGLVertexArray : public IVertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void Bind() override;
		void Unbind() override;

		/**
		 * \brief Add by binding the vertex buffer into vertex array, the parameter is taking reference so it wont count up the reference count of shared pointer
		 * \param buffer reference of shared pointer of IVertexBuffer child
		 * \param bindIndex vertex buffer binding index in vertex array
		 */
		void AddVertexBuffer(std::shared_ptr<IVertexBuffer>& buffer, int bindIndex) override;
		void SetIndexBuffer(std::shared_ptr<IIndexBuffer>& buffer) override;

		[[nodiscard]] const std::vector<std::shared_ptr<IVertexBuffer>>& GetVertexBuffers() const override;
		[[nodiscard]] const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const override;

	private:
		std::vector<std::shared_ptr<IVertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IIndexBuffer> m_indexBuffer;
	};
}