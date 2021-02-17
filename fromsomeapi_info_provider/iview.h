#pragma once

#include "model.hpp"

#include <string>

class IView
{
public:
	virtual void get(Model const&) const noexcept = 0;
};
