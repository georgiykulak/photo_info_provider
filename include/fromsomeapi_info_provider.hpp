#ifndef PHOTO_INFO_PROVIDER_MAIN_HPP
#define PHOTO_INFO_PROVIDER_MAIN_HPP

#include <controller.hpp>
#include <model_unsplash.hpp>
#include <view_cli.hpp>
#include <curl_sender.hpp>

void defMain ()
{
	std::unique_ptr< IModel > modelPtr( std::make_unique< ModelUnsplash >() );
	
	std::unique_ptr< IView > viewPtr( std::make_unique< ViewCLI >() );
	
	Controller controller( std::move( modelPtr ), std::move( viewPtr ) );

	controller.fetchContent();

	controller.getResult();
}

#endif // PHOTO_INFO_PROVIDER_MAIN_HPP //
