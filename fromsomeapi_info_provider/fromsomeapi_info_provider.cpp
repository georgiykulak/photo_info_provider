#include "controller.h"
#include "cli_view.h"
#include "curl_sender.h"

int main( int argc, char* argv[] )
{
	std::string const apiLink = "https://api.unsplash.com/";

	std::unique_ptr< IView > viewPtr( std::make_unique< CLIView >() );

	Model model = getModel(viewPtr, apiLink);

	Controller controller( model, viewPtr );

	controller.getResult();

	return 0;
}
