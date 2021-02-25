#pragma once

#include <imodel.hpp>

#include <memory>

class IView
{
public:
	virtual void readUsername ( std::string & ) const = 0;

	virtual void readPassword ( std::string & ) const = 0;
	
	virtual void readAssetNumber ( std::size_t & ) const = 0;
	
	virtual void get ( std::unique_ptr< IModel > const & ) const = 0;
};
