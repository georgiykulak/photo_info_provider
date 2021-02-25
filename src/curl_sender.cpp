#include <curl_sender.hpp>

static std::size_t WriteDataCallback (
	char * in,
	std::size_t size,
	std::size_t nmemb,
	std::string * out
)
{
	if ( !in )
		return 0;

	auto writeSize = size * nmemb;
	out->append( in, writeSize );

	return writeSize;
}

std::string sendAndGet (
	std::string const & link,
	std::string const & auth
)
{
	CURL* curl = curl_easy_init();

	if ( !curl )
		return R"("response":{"500":"Internal Server Error"})";

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

	return response;
}
