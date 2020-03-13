#pragma once

#include "JEpch.h"

namespace JEngine {

	enum class ShaderDataType {
		None = 0,
		Float,Float2,Float3,Float4,
		Mat3,Mat4,
		Int,Int2,Int3,Int4,
		Bool
	};
	
	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch(type) {
		case ShaderDataType::Float:      return 4;
		case ShaderDataType::Float2:     return 4 * 2;
		case ShaderDataType::Float3:     return 4 * 3;
		case ShaderDataType::Float4:     return 4 * 4;
		case ShaderDataType::Mat3:       return 4 * 3 * 3;
		case ShaderDataType::Mat4:       return 4 * 4 * 4;
		case ShaderDataType::Int:        return 4;
		case ShaderDataType::Int2:       return 4 * 2;
		case ShaderDataType::Int3:       return 4 * 3;
		case ShaderDataType::Int4:       return 4 * 4;
		case ShaderDataType::Bool:       return 1;
		}
		JE_CORE_ASSERT(false, "invalid ShaderDataType");
		return 0;
	}

	struct BufferElement {
		BufferElement(const std::string& name, ShaderDataType type)
			:m_Name(name), m_Type(type) , m_Offset(0),normalized(false){
			m_Size = ShaderDataTypeSize(type);
		}
		uint32_t GetComponentCount() const {
			switch (m_Type) {
			case ShaderDataType::Float:      return 1;
			case ShaderDataType::Float2:     return 2;
			case ShaderDataType::Float3:     return 3;
			case ShaderDataType::Float4:     return 4;
			case ShaderDataType::Mat3:       return 3 * 3;
			case ShaderDataType::Mat4:       return 4 * 4;
			case ShaderDataType::Int:        return 1;
			case ShaderDataType::Int2:       return 2;
			case ShaderDataType::Int3:       return 3;
			case ShaderDataType::Int4:       return 4;
			case ShaderDataType::Bool:       return 1;
			}
			JE_CORE_ASSERT(false, "invalid ShaderDataType");
			return 0;
		}

		std::string m_Name;
		ShaderDataType m_Type;
		uint32_t m_Offset;
		uint32_t m_Size;
		bool normalized;
	};

	class BufferLayout {
	public:
		BufferLayout(){}

		BufferLayout(const std::initializer_list<BufferElement>& layout) 
			:m_BufferLayout(layout){
			CalcOffsetAndStride();
		}
		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetBufferLayout() const { return m_BufferLayout; }

		std::vector<BufferElement>::iterator begin() { return m_BufferLayout.begin(); }
		std::vector<BufferElement>::iterator end() { return m_BufferLayout.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_BufferLayout.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_BufferLayout.end(); }

	private:
		void CalcOffsetAndStride() {
			uint32_t sum = 0;
			m_Stride = 0;
			for(auto &element : m_BufferLayout){
				element.m_Offset = sum;
				sum += element.m_Size;
				m_Stride += element.m_Size;
			}
		}

		std::vector<BufferElement> m_BufferLayout;
		uint32_t m_Stride;
	};
}