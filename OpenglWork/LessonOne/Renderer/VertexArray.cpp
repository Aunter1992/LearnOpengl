#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererId);
}
void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererId);
}
void  VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& element = layout.GetElements();
	unsigned int offect = 0;
	for (unsigned int  i = 0; i < element.size(); i++)
	{
		auto& e = element[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.GetStride(), (void*)offect);
		offect += e.count * VertexBufferElement::GetBufferSize(e.type);

	}
}
