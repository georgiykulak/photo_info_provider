#pragma once

#include <curl_sender.hpp>

#include <single_include/nlohmann/json.hpp>

using json = nlohmann::json;

class ModelUnsplash final : public IModel
{
public:
	ModelUnsplash () = default;

	void fetch (
		std::string const & user,
		std::string const & access_key
	) override;

	void set ( std::string const & str ) override;

	void setAssetNumber ( std::size_t const index ) noexcept override;

	void parse () override;

	unsigned getSuccessCode () const noexcept override;

	std::pair< unsigned, std::string > const & getResponse ()
	const noexcept override;

	std::string const & getFilename () const noexcept override;

	std::size_t getFilesize () const noexcept override;

	std::string const & getModifiedTime () const noexcept override;

	std::string const & getUploadTime () const noexcept override;

	std::string const & getDescription () const noexcept override;

	std::string const & getLinkToPhoto () const noexcept override;

private:
	inline static std::string_view constexpr s_apiLink =
													"https://api.unsplash.com/";

	json m_rawJSON = json::array();
	std::pair< unsigned, std::string > m_response;
	std::string m_filename;
	std::string m_modifiedTime;
	std::string m_uploadTime;
	std::string m_description;
	std::string m_linkToPhoto;
	std::size_t m_assetNumber = 0;
	std::size_t m_filesize = 0;
};
