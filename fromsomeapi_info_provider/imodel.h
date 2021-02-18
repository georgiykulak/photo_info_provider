#pragma once

#include <string>

class IModel
{
public:
	virtual void set(std::string const&) = 0;

	virtual void setAssetNumber(std::size_t const) noexcept = 0;

	virtual void parse() = 0;

	virtual unsigned getSuccessCode() const noexcept = 0;

	virtual std::pair<unsigned, std::string> const& getResponse() const noexcept = 0;

	virtual std::string const& getFilename() const noexcept = 0;
	
	virtual std::size_t getFilesize() const noexcept = 0;

	virtual std::string const& getModifiedTime() const noexcept = 0;
	
	virtual std::string const& getUploadTime() const noexcept = 0;
};