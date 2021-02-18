#pragma once

#include "imodel.h"

#include "../json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class Model final : public IModel
{
public:
	Model() = default;

	void set(std::string const& str) override
	{
		m_rawJSON = json::parse(str);
	}

	void setAssetNumber(std::size_t const index) noexcept override
	{
		m_assetNumber = index;
	}

	void parse() override
	{
		json assetJSON;

		try
		{
			assetJSON = m_rawJSON.at(m_assetNumber);
		}
		catch (json::out_of_range const&)
		{
			m_rawJSON =
				json({ "error",
					"The index " + std::to_string(m_assetNumber) + " is out of range" });
		}
		catch (std::exception const&)
		{
			m_rawJSON = json({ "error", "Can't access array of assets by an index" });
		}

		if (assetJSON.contains("id"))
			m_filename = assetJSON["id"];

		if (assetJSON.contains("width") && assetJSON.contains("height"))
			m_filesize =
				assetJSON["width"].get< std::size_t >() *
				assetJSON["height"].get< std::size_t >();

		if (assetJSON.contains("created_at"))
			m_uploadTime = assetJSON["created_at"];

		if (assetJSON.contains("updated_at"))
			m_modifiedTime = assetJSON["updated_at"];
	}

	virtual std::string const& getFilename() noexcept override
	{
		return m_filename;
	}

	virtual std::size_t getFilesize() noexcept override
	{
		return m_filesize;
	}

	virtual std::string const& getModifiedTime() noexcept override
	{
		return m_modifiedTime;
	}

	virtual std::string const& getUploadTime() noexcept override
	{
		return m_uploadTime;
	}

private:
	json m_rawJSON = json::array();
	std::string m_filename;
	std::string m_modifiedTime;
	std::string m_uploadTime;
	std::size_t m_assetNumber = 0;
	std::size_t m_filesize = 0;
};
