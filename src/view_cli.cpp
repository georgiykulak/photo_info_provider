#include <view_cli.hpp>

void ViewCLI::readUsername ( std::string & username ) const
{
	std::cout << "Enter username: ";
	std::cin >> username;
}

void ViewCLI::readPassword ( std::string & password ) const
{
	std::cout << "Enter password: ";
	std::cin >> password;
}
	
void ViewCLI::readAssetNumber ( std::size_t & index ) const
{
	std::cout << "Enter the number of the asset to get info from: ";
	std::cin >> index;
}

void ViewCLI::get ( std::unique_ptr< IModel > const & modelPtr ) const
{
    json res;
    
    auto const & resPair = modelPtr->getResponse();
    res[ "response" ][ std::to_string( resPair.first ) ] = resPair.second;

    if ( resPair.first == modelPtr->getSuccessCode() )
    {
        res[ "filename" ] = modelPtr->getFilename();
        res[ "filesize" ] = modelPtr->getFilesize();
        res[ "modifiedTime" ] = modelPtr->getModifiedTime();
        res[ "uploadTime" ] = modelPtr->getUploadTime();
        if ( !modelPtr->getDescription().empty() )
            res[ "description" ] = modelPtr->getDescription();
        res[ "linkToPhoto" ] = modelPtr->getLinkToPhoto();
    }

    std::cout << res.dump() << std::endl;
}
