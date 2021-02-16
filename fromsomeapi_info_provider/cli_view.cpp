#include "cli_view.h"

void CLIView::set(std::string& username, std::string& password) const
{
	std::cout << "Enter username: ";
	std::cin >> username;

	std::cout << "Enter password: ";
	std::cin >> password;
}

void CLIView::get(Model const& model) const noexcept
{
	std::cout << model.get() << std::endl;
}