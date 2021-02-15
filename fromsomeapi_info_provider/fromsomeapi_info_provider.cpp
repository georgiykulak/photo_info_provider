#include <iostream>
#include <curl\curl.h>

std::size_t WriteDataCallback( char * in, std::size_t size, std::size_t nmemb, std::string * out )
{
	if ( !in )
		return 0;

	auto writeSize = size * nmemb;
	out->append( in, writeSize );

	return writeSize;
}

int main( int argc, char* argv[] )
{
	CURL * curl = curl_easy_init();

	if ( !curl )
	{
		std::cout << "Unknown error happened on curl_easy_init()\n\n";

		return 1;
	}

	curl_easy_setopt( curl, CURLOPT_CUSTOMREQUEST, "GET" );
	curl_easy_setopt( curl, CURLOPT_URL, "https://currency-converter5.p.rapidapi.com/currency/convert?format=json&from=USD&to=UAH&amount=1200&language=en" );

	struct curl_slist * headers = nullptr;
	headers = curl_slist_append( headers, "x-rapidapi-key: ffe3711fc7mshb5178c5639ffd04p1bd34ajsn8b932956cd90" );
	headers = curl_slist_append( headers, "x-rapidapi-host: currency-converter5.p.rapidapi.com" );
	curl_easy_setopt( curl, CURLOPT_HTTPHEADER, headers );
	curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, WriteDataCallback );
	std::string response;
	curl_easy_setopt( curl, CURLOPT_WRITEDATA, &response );

	curl_easy_perform( curl );
		
	curl_easy_cleanup( curl );

	// TODO: Remove following code
	std::cout << "done:\n\n";
	std::cout << "<\n" << response << ">\n\n";

	return 0;
}
