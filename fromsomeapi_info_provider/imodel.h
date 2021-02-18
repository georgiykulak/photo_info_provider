#pragma once

#include <string>

class IModel
{
public:
	virtual void set(std::string const&) = 0;

	virtual void setAssetNumber(std::size_t const) noexcept = 0;

	virtual void parse() = 0;

	virtual std::string const& getFilename() noexcept = 0;
	
	virtual std::size_t getFilesize() noexcept = 0;

	virtual std::string const& getModifiedTime() noexcept = 0;
	
	virtual std::string const& getUploadTime() noexcept = 0;
};