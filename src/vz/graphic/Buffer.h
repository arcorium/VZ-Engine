#pragma once

namespace vz
{

	enum class ShaderType : uint8_t
	{
		None = 0,

		Int,
		UInt,
		Float,
		UShort,
		Bool,

		Vec2I,
		Vec2F,
		Vec3I,
		Vec3F,
		Vec4I,
		Vec4F,

		Mat3I,
		Mat3F,
		Mat4I,
		Mat4F

	};

	inline int GetSizeOfShaderType (const ShaderType& type)
	{
		switch (type)
		{
		case ShaderType::None: break;
		case ShaderType::Int: 
		case ShaderType::UInt: 
		case ShaderType::Float:		return 4;
		case ShaderType::UShort:	return 2;
		case ShaderType::Bool:		return 1;
		case ShaderType::Vec2I:		
		case ShaderType::Vec2F:		return 2 * 4;
		case ShaderType::Vec3I:		
		case ShaderType::Vec3F:		return 3 * 4;
		case ShaderType::Vec4I:		
		case ShaderType::Vec4F:		return 4 * 4;
		case ShaderType::Mat3I:		
		case ShaderType::Mat3F:		return 3 * 3 * 4;
		case ShaderType::Mat4I:		
		case ShaderType::Mat4F:		return 4 * 4 * 4;
		default: ;
		}

		VZ_CORE_ASSERT(false, "shader type not found");
		return 0;
	}

	inline int GetCountOfShaderType (const ShaderType& type)
	{
		switch (type)
		{
		case ShaderType::None: break;
		case ShaderType::Int:
		case ShaderType::UInt:
		case ShaderType::Float:		
		case ShaderType::UShort:	
		case ShaderType::Bool:		return 1;
		case ShaderType::Vec2I:		
		case ShaderType::Vec2F:		return 2;
		case ShaderType::Vec3I:		
		case ShaderType::Vec3F:		return 3;
		case ShaderType::Vec4I:		
		case ShaderType::Vec4F:		return 4;
		case ShaderType::Mat3I:		
		case ShaderType::Mat3F:		return 3 * 3;
		case ShaderType::Mat4I:		
		case ShaderType::Mat4F:		return 4 * 4;
		default:;
		}

		VZ_CORE_ASSERT(false, "shader type not found");
		return 0;
	}

	struct BufferElement
	{
		int Size;
		ShaderType Type;
		bool Normalized;
		unsigned Offset;

		BufferElement()
			: Size(0), Type(ShaderType::None), Normalized(false), Offset(0) {}

		BufferElement(ShaderType type, bool isNormalized = false)
			: Size(GetSizeOfShaderType(type)), Type(type), Normalized(isNormalized), Offset(0) {}
	};


	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& list) noexcept
			: m_elements(list), m_stride(0)
		{
			Init();
		}
		virtual ~BufferLayout() = default;

		const std::vector<BufferElement>& GetElements() const { return m_elements; }
		void SetElements(const std::vector<BufferElement>& elements) { m_elements = elements; }
		void SetElements(const std::initializer_list<BufferElement>& elements) { m_elements = std::vector<BufferElement>{elements}; }

		// Iterator
		std::vector<BufferElement>::iterator begin() noexcept { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() noexcept { return m_elements.end(); }
		[[nodiscard]] std::vector<BufferElement>::const_iterator begin() const noexcept { return m_elements.cbegin(); }
		[[nodiscard]] std::vector<BufferElement>::const_iterator end() const noexcept { return m_elements.cend(); }

		int GetStride() const { return m_stride; }

	private:
		virtual void Init()
		{
			SetElementAttribute();
		}

		/**
		 * \brief Set element attribute that only can be set when the layout is already defined completely (Offset and Stride)
		 */
		void SetElementAttribute()
		{
			unsigned offset = 0;
			//std::vector<unsigned> offset{10, 0, std::allocator<unsigned>{}};
			for (auto& element : m_elements)
			{
				element.Offset = offset;
				// Set Offset
				offset += element.Size;
				// Set Stride
				m_stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_elements;
		int m_stride;
	};

	namespace detail
	{
		/**
		 * \brief Interface class of buffer for the actual data (m_id)
		 */
		class IBuffer
		{
		public:
			IBuffer() : m_id(0) {};
			virtual ~IBuffer() = default;

			[[nodiscard]] virtual unsigned Get() const { return m_id; };

		protected:
			// Will be always set to protected for all derived of derived classes
			unsigned m_id;
		};
	}

	/**
	 * \brief Interface of Vertex Buffer (Should be derived for use)
	 */
	class VZ_API IVertexBuffer : public detail::IBuffer
	{
	public:
		IVertexBuffer() = default;
		virtual ~IVertexBuffer() = default;

		virtual void SetData(unsigned size, const void* data) = 0;
		virtual void SetSubData(unsigned size, unsigned offset, const void* data) = 0;
		inline virtual void SetStorage(unsigned size, const void* data) { SetData(size, data); };

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual unsigned GetSize() const = 0;

		/**
		 * \brief Construct and allocating VertexBuffer into heap memory
		 * \param size size of vertices in bytes
		 * \param data pointer into data
		 * \return Raw pointer of heap allocated
		 */
		static IVertexBuffer* Create(unsigned size, const void* data);

		/**
		 * \brief Construct and allocating VertexBuffer into heap memory
		 * \param size size of vertices in bytes
		 * \param data pointer into data
		 * \return Shared pointer
		 */
		static std::shared_ptr<IVertexBuffer> CreateShared(unsigned size, const void* data);

	};

	/**
	 * \brief Interface of Index Buffer (Should be derived for use)
	 */
	class VZ_API IIndexBuffer : public detail::IBuffer
	{
	public:
		IIndexBuffer() = default;
		virtual ~IIndexBuffer() = default;


		virtual void SetData(unsigned size, const void* data) = 0;
		virtual void SetSubData(unsigned size, unsigned offset, const void* data) = 0;
		inline virtual void SetStorage(unsigned size, const void* data) { SetData(size, data); };

		virtual int GetCount() const = 0;

		/**
		 * \brief Construct and allocating IndexBuffer into heap memory
		 * \param size size of indices in bytes
		 * \param data pointer into data
		 * \return Raw pointer of heap allocated
		 */
		static IIndexBuffer* Create(unsigned size, const void* data);

		/**
		 * \brief Construct and allocating IndexBuffer into heap memory
		 * \param size size of indices in bytes
		 * \param data pointer into data
		 * \return Shared pointer
		 */
		static std::shared_ptr<IIndexBuffer> CreateShared(unsigned size, const void* data);

	};
}
