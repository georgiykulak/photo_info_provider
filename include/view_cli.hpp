#pragma once

#include <iview.hpp>

#include <iostream>

#include "../json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class ViewCLI final : public IView
{
public:
	void readUsername ( std::string & ) const override;

	void readPassword ( std::string & ) const override;
	
	void readAssetNumber ( std::size_t & ) const override;
	
	void get ( std::unique_ptr< IModel > const & ) const override;
};
