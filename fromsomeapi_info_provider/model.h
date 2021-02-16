#pragma once

#include <string>

class Model
{
public:
	Model() = default;

	Model(std::string const& str);

	virtual void set(std::string const& str);

	virtual std::string const& get() const noexcept;

private:
	std::string m_data;
};
