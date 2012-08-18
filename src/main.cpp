/*
+=======================================================+
|	Name        : Mimir's Well							|
|	Author      : Matthew Frost							|
|	Version     : 0.1									|
|	Copyright   : "BEER-WARE LICENSE"					|
|	Description : Stock Market Sentiment Analyzer		|
+=======================================================+
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>

void apitest();

int main(int argc, char * argv[]) {
	std::cout << "testing twitter api" << std::endl;
	apitest();
	return 0;
}

int curlWrite(char * data, size_t size, size_t len, std::string * buffer) {
	int result = 0;
	if (buffer != NULL) {
		buffer->append(data, size * len);
		result = size * len;
	}
	return result;
}

void apitest() {
	std::cout << "searching twitter for '$QQQ'" << std::endl;
	CURL * curl;
	std::string buffer;
	std::string testurl = "http://search.twitter.com/search.json?q=$QQQ";
	const char * url = testurl.c_str();
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	std::cout << buffer << std::endl;
}
