#pragma once

#include <imodel.hpp>

#include <memory>

#include <curl\curl.h>

void sendGetRequest (
	std::string &,
	std::string const & link,
	std::string const & auth
);
