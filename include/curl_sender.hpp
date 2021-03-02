#ifndef PHOTO_INFO_PROVIDER_CURL_SENDER_HPP
#define PHOTO_INFO_PROVIDER_CURL_SENDER_HPP

#include <imodel.hpp>

#include <memory>

#include <curl\curl.h>

void sendGetRequest (
	std::string &,
	std::string const & link,
	std::string const & auth
);

#endif // PHOTO_INFO_PROVIDER_CURL_SENDER_HPP //
