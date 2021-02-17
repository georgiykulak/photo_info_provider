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
		// TODO: Reparse JSON
		m_cleanData = m_rawData; // TODO: Remove it !!!
	}

private:
	std::string m_rawData;
	std::string m_cleanData;
};
