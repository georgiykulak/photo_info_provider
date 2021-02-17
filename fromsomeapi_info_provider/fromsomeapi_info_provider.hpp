#pragma once

#include "controller.hpp"
#include "cli_view.hpp"
#include "curl_sender.hpp"

void defMain()
{
	std::string const apiLink = "https://api.unsplash.com/";

	std::unique_ptr< IView > viewPtr(std::make_unique< CLIView >());

	std::string username;
	std::cout << "Enter username: ";
	std::cin >> username;

	std::string password;
	std::cout << "Enter password: ";
	std::cin >> password;

	Model model = getModel(username, password, apiLink);

	Controller controller(model, viewPtr);

	controller.getResult();
}
