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

		if (!m_rawJSON.is_array() && m_rawJSON.contains("errors"))
		{
			if (m_rawJSON["errors"].is_array())
			{
				std::string str = m_rawJSON["errors"].at(0).get<std::string>();
				
				if (str.rfind("OAuth error", 0) == 0)
					m_response = { 401, "User is not authenticated" };
				
				return;
			}
		}

		try
		{
			assetJSON = m_rawJSON.at(m_assetNumber);
		}
		catch (json::out_of_range const&)
		{
			m_response = { 404, "Asset does not exist" };
			return;
		}
		catch (std::exception const&)
		{
			m_response = { 404, "Asset does not exist" };
			return;
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

		m_response = { getSuccessCode(), "The operation was successful" };
	}

	unsigned getSuccessCode() const noexcept override
	{
		return 200;
	}

	std::pair<unsigned, std::string> const& getResponse() const noexcept override
	{
		return m_response;
	}

	std::string const& getFilename() const noexcept override
	{
		return m_filename;
	}

	std::size_t getFilesize() const noexcept override
	{
		return m_filesize;
	}

	std::string const& getModifiedTime() const noexcept override
	{
		return m_modifiedTime;
	}

	std::string const& getUploadTime() const noexcept override
	{
		return m_uploadTime;
	}

private:
	json m_rawJSON = json::array();
	std::pair<unsigned, std::string> m_response;
	std::string m_filename;
	std::string m_modifiedTime;
	std::string m_uploadTime;
	std::size_t m_assetNumber = 0;
	std::size_t m_filesize = 0;
};
