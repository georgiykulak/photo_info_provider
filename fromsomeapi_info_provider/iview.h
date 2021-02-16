#pragma once

#include "model.h"

#include <string>

class IView
{
public:
	virtual void set(std::string&, std::string&) const = 0;

	virtual void get(Model const&) const noexcept = 0;
};