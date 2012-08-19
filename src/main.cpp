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
#include "twitter.h"

void apitest();

int main(int argc, char * argv[]) {
	std::cout << "testing twitter class" << std::endl;
	Twitter twitter;

//	apitest();
	return 0;
}

void apitest() {
	std::cout << "searching twitter for '$QQQ'" << std::endl;
	CURL * curl;
	std::string buffer;
//	std::string testurl = "http://search.twitter.com/search.json?q=$QQQ";
	std::string testurl = "http://127.0.0.1/test.json";
	const char * url = testurl.c_str();
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

//	std::cout << buffer << std::endl;
}
