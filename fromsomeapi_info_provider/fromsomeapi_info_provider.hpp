#pragma once

#include "controller.hpp"
#include "cli_view.hpp"
#include "curl_sender.hpp"

void defMain()
{
	std::string const apiLink = "https://api.unsplash.com/";

	std::unique_ptr< IView > viewPtr(std::make_unique< CLIView >());

	Model model = getModel(viewPtr, apiLink);

	Controller controller(model, viewPtr);

	controller.getResult();
}
