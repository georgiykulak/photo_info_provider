#include "model.h"

Model::Model(std::string const& str)
{
	set(str);
}

void Model::set(std::string const& str)
{
	m_data = str;
}

std::string const& Model::get() const noexcept
{
	return m_data;
}
