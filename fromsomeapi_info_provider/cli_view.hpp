#pragma once

#include "iview.h"

#include <iostream>

#include "json_parser.hpp"

class CLIView final : public IView
{
public:
	void get(Model const& model) const noexcept override
	{
		std::cout << parseJSON( model.get(), 0 ).dump() << std::endl;
	}
};
