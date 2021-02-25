#pragma once

#include "imodel.h"

#include <memory>

class IView
{
public:
	virtual void get(std::unique_ptr< IModel > const&) const = 0;
};
