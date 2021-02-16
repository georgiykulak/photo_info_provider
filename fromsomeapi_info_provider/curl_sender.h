#pragma once

#include "iview.h"

#include <curl\curl.h>

#include <memory>

std::size_t WriteDataCallback(char* in, std::size_t size, std::size_t nmemb, std::string* out);

void send(Model& model, std::string const& link, std::string const& auth);

Model getModel(std::unique_ptr< IView > const& viewPtr, std::string const& apiLink);
