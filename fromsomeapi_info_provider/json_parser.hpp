#pragma once

#include <string>
#include <iostream>

#include "../json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

json parseJSON(json const& rawJSON, std::size_t index)
{
	json rawAsset;
	json cleanJSON;

	if (!rawJSON.is_array())
		return json({ "error", "Got not an array of assets" });

	try
	{
		rawAsset = rawJSON.at(index);
	}
	catch (json::out_of_range const&)
	{
		return json({ "error", "The index " + std::to_string(index) + " is out of range" });
	}
	catch (std::exception const&)
	{
		return json({ "error", "Can't access array of assets by an index" });
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

	return cleanJSON;
}
