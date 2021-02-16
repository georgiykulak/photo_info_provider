#pragma once

#include <string>

class Model
{
public:
	Model() = default;

	Model(std::string const& str)
	{
		set(str);
	}

	virtual void set(std::string const& str)
	{
		m_data = str;
	}

	virtual std::string const& get() const noexcept
	{
		return m_data;
	}

private:
	std::string m_data;
};
