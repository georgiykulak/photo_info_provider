#pragma warning(disable : 4996)

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <curl\curl.h>

size_t write_data( void* ptr, size_t size, size_t nmemb, FILE* stream )
{
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

int main( int argc, char* argv[] )
{
	//BuildBT(10);
	CURL* curl;
	CURLcode res;
	FILE* fp;
	char outfilename[] = "C:\\Users\\Georgiy\\Projects\\fromsomeapi_info_provider\\out.html";
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(outfilename, "wb");
		
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(curl, CURLOPT_URL, "https://currency-converter5.p.rapidapi.com/currency/convert?format=json&from=USD&to=UAH&amount=1200&language=en");

		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "x-rapidapi-key: ffe3711fc7mshb5178c5639ffd04p1bd34ajsn8b932956cd90");
		headers = curl_slist_append(headers, "x-rapidapi-host: currency-converter5.p.rapidapi.com");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		res = curl_easy_perform(curl);
		
		curl_easy_cleanup(curl);
		fclose(fp);
	}

	std::cout << "done" << std::endl;
	return 0;
}
