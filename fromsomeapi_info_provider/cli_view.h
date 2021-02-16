#pragma once

#include "iview.h"

#include <iostream>

class CLIView final : public IView
{
public:
	void set(std::string& username, std::string& password) const override;

	void get(Model const& model) const noexcept override;
};
