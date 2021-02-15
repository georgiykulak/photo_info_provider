// fromsomeapi_info_provider.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning(disable : 4996)

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "curl\curl.h"
using namespace std;


size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

int main(int n, char* args[])
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
		curl_easy_setopt(curl, CURLOPT_URL, "https://deezerdevs-deezer.p.rapidapi.com/search?q=eminem");

		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "x-rapidapi-key: ffe3711fc7mshb5178c5639ffd04p1bd34ajsn8b932956cd90");
		headers = curl_slist_append(headers, "x-rapidapi-host: deezerdevs-deezer.p.rapidapi.com");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		res = curl_easy_perform(curl);
		
		curl_easy_cleanup(curl);
		fclose(fp);
	}

	cout << "done" << endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
