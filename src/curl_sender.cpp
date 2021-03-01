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

void sendGetRequest (
	std::string & response,
	std::string const & link,
	std::string const & auth
)
{
	CURL* curl = curl_easy_init();

	if ( !curl )
	{
		response = R"("response":{"503":"Service Unavailable"})";
		return;
	}

	curl_easy_setopt( curl, CURLOPT_CUSTOMREQUEST, "GET" );
	curl_easy_setopt( curl, CURLOPT_URL, link.c_str() );

	struct curl_slist* headers = nullptr;

	headers = curl_slist_append( headers, auth.c_str() );
	curl_easy_setopt( curl, CURLOPT_HTTPHEADER, headers );
	curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteDataCallback );

	curl_easy_setopt( curl, CURLOPT_WRITEDATA, &response );

	curl_easy_perform( curl );
	curl_easy_cleanup( curl );
}
