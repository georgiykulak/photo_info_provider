#pragma once

#include "iview.h"

#include <curl\curl.h>

#include <memory>

std::size_t WriteDataCallback(char* in, std::size_t size, std::size_t nmemb, std::string* out);

void send(Model& model, std::string const& link, std::string const& auth);

Model getModel(std::unique_ptr< IView > const& viewPtr, std::string const& apiLink);



std::size_t WriteDataCallback(char* in, std::size_t size, std::size_t nmemb, std::string* out)
{
	if (!in)
		return 0;

	auto writeSize = size * nmemb;
	out->append(in, writeSize);

	return writeSize;
}

void send(Model& model, std::string const& link, std::string const& auth)
{
	CURL* curl = curl_easy_init();

	if (!curl)
		return;

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(curl, CURLOPT_URL, link.data());

	struct curl_slist* headers = nullptr;

	headers = curl_slist_append(headers, auth.data());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallback);

	std::string response;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	model.set(response);
}

Model getModel(std::string user, std::string access_key, std::string const& apiLink)
{
	Model model;

	std::string const link = apiLink + "users/" + user + "/photos/";
	std::string const auth = "Authorization: Client-ID " + access_key;
	send(model, link, auth);

	if (model.get().empty())
		return Model( R"({"error":"Something wrong happened on curl_easy_init"})" );

	return model;
}

