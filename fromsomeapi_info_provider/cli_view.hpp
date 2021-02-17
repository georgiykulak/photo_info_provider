#pragma once

#include "iview.h"

#include <iostream>

#include "json_parser.hpp"

class CLIView final : public IView
{
public:
	void setAssetNumber(std::size_t const index) noexcept override
	{
		m_index = index;
	}

	void get(Model const& model) const noexcept override
	{
		std::cout << parseJSON( model.get(), m_index ).dump() << std::endl;
	}
private:
	std::size_t m_index = 0;
};
