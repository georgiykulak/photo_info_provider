#pragma once

#include "model.hpp"

#include <string>

class IView
{
public:
	virtual void setAssetNumber(std::size_t const) noexcept = 0;

	virtual void get(Model const&) const noexcept = 0;
};
