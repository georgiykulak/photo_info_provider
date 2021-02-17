#pragma once

#include "json_parser.hpp"

class Model
{
public:
	Model() = default;

	Model(std::string const& str)
	{
		set(str);
	}

	void set(std::string const& str)
	{
		m_rawData = str;

		reparse();
	}

	std::string const& getRaw() const noexcept
	{
		return m_rawData;
	}

	std::string const& get() const noexcept
	{
		return m_cleanData;
	}

	virtual void reparse()
	{
		m_cleanData = parseJSON( m_rawData, 0 );
	}

private:
	std::string m_rawData;
	std::string m_cleanData;
};
