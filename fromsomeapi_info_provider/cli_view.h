#pragma once

#include "iview.h"

#include <iostream>

class CLIView final : public IView
{
public:
	void set(std::string& username, std::string& password) const override
	{
		std::cout << "Enter username: ";
		std::cin >> username;

		std::cout << "Enter password: ";
		std::cin >> password;
	}

	void get(Model const& model) const noexcept override
	{
		std::cout << model.get() << std::endl;
	}
};
