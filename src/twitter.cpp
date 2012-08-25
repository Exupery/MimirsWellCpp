/*
 * twitter.cpp
 *
 *  Created on: Aug 18, 2012
 *      Author: frost
 */

#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include "twitter.h"
#include "parser.h"

Twitter::Twitter() {

}

Twitter::~Twitter() {

}

std::set<Tweet> Twitter::search(const std::string &symbol) {
	std::string url = buildInitialSearchURL(symbol);
	std::string results = curlRead(url);
	Parser parser;
	std::string next = parser.parseNextPage(results);
	std::cout << buildNextSearchURL(next) << std::endl; //DELME
	std::set<Tweet> tweets = parser.parseResults(results);
	return tweets;
}

std::string Twitter::buildInitialSearchURL(const std::string &symbol) {
	std::string url = BASE_URL + std::string("?lang=en&q=%24") + symbol;
	return url;
}

std::string Twitter::buildNextSearchURL(const std::string &next) {
	std::string url = BASE_URL + next;
	return url;
}

std::string Twitter::curlRead(const std::string &searchURL) {
	CURL * curl;
	std::string buffer;
	const char * url = searchURL.c_str();
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	return buffer;
}

int Twitter::curlWrite(char * data, size_t size, size_t len, std::string * buffer) {
	int result = 0;
	if (buffer != NULL) {
		buffer->append(data, size * len);
		result = size * len;
	}
	return result;
}

