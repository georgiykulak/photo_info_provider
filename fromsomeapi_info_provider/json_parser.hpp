#pragma once

#include <string>
#include <iostream>

#include "../json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

auto parseJSON(std::string const& rawStr, std::size_t index)
{
	auto rawJSON = json::parse(rawStr);
	json cleanJSON;
	json rawAsset;

	if (!rawJSON.is_array())
	{
		cleanJSON["error"] = "Got not an array of assets";
		return cleanJSON.dump();
	}

	try
	{
		rawAsset = rawJSON[index];
	}
	catch (std::out_of_range const&)
	{
		cleanJSON["error"] = "The index " + std::to_string( index ) + " is out of range";
		return cleanJSON.dump();
	}

	if (rawAsset.contains("id"))
		cleanJSON["filename"] = rawAsset["id"];

	if (rawAsset.contains("width") && rawAsset.contains("height"))
		cleanJSON["filesize"] =
			rawAsset["width"].get< std::size_t >() * rawAsset["height"].get< std::size_t >();

	if (rawAsset.contains("created_at"))
		cleanJSON["uploadTime"] = rawAsset["created_at"];

	if (rawAsset.contains("updated_at"))
		cleanJSON["modifiedTime"] = rawAsset["updated_at"];

	return cleanJSON.dump();
}
