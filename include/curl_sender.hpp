#pragma once

#include <imodel.hpp>

#include <memory>

#include <curl\curl.h>

std::string sendAndGet (
	std::string const & link,
	std::string const & auth
);
