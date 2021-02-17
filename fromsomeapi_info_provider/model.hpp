#pragma once

#include "../json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

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
		m_rawJSON = json::parse(str);
	}

	json const& get() const noexcept
	{
		return m_rawJSON;
	}

private:
	json m_rawJSON;
};
