#pragma once

#include "controller.hpp"
#include "model.hpp"
#include "cli_view.hpp"
#include "curl_sender.hpp"

void defMain()
{
	std::string const apiLink = "https://api.unsplash.com/";

	std::string username;
	std::cout << "Enter username: ";
	std::cin >> username;

	std::string password;
	std::cout << "Enter password: ";
	std::cin >> password;

	std::size_t index;
	std::cout << "Enter the number of the asset to get info from: ";
	std::cin >> index;

	std::unique_ptr< IModel > modelPtr(std::make_unique< Model >());
	
	getModel(modelPtr, username, password, apiLink);

	std::unique_ptr< IView > viewPtr(std::make_unique< CLIView >());
	
	Controller controller(std::move(modelPtr), std::move(viewPtr));

	controller.chooseAsset( index );

	controller.getResult();
}
