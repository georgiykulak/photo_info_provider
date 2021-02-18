#pragma once

#include "iview.h"

#include <iostream>

#include "../json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class CLIView final : public IView
{
public:
	void get(std::unique_ptr< IModel > const& modelPtr) const override
	{
		json res;
		
		auto const & resPair = modelPtr->getResponse();
		res["response"][std::to_string(resPair.first)] = resPair.second;

		if (resPair.first == modelPtr->getSuccessCode())
		{
			res["filename"] = modelPtr->getFilename();
			res["filesize"] = modelPtr->getFilesize();
			res["modifiedTime"] = modelPtr->getModifiedTime();
			res["uploadTime"] = modelPtr->getUploadTime();
		}

		std::cout << res.dump() << std::endl;
	}
};
