#pragma once
#include "Buffer.h"

namespace vz
{
	/**
	 * \brief Interface of Vertex Array.
	 * This class is responsible for deleting the index buffer and vertex buffer when dealing with raw pointer.
	 */
	class VZ_API IVertexArray : public detail::IBuffer
	{
	public:
		IVertexArray() = default;
		~IVertexArray() override = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(std::shared_ptr<IVertexBuffer>& buffer, int bindIndex = 0) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IIndexBuffer>& buffer) = 0;

		[[nodiscard]] virtual const std::vector<std::shared_ptr<IVertexBuffer>>& GetVertexBuffers() const = 0;
		[[nodiscard]] virtual const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const = 0;

		/**
		 * \brief Construct and allocating VertexArray into heap memory
		 * \return Raw pointer
		 */
		static IVertexArray* Create();

		/**
		 * \brief Construct and allocating VertexArray into heap memory
		 * \return Shared pointer
		 */
		static std::shared_ptr<IVertexArray> CreateShared();
	};
}
