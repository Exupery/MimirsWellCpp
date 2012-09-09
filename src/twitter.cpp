/*
 * twitter.cpp
 *
 *  Created on: Aug 18, 2012
 *      Author: frost
 */

#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <curl/easy.h>
#include "dbhandler.h"
#include "twitter.h"
#include "parser.h"

Twitter::Twitter() {

}

Twitter::~Twitter() {

}

std::set<Tweet> Twitter::search(const std::string& symbol) {
	Parser parser;
	std::string url = buildInitialSearchURL(symbol);
	std::string results = curlRead(url);
	std::set<Tweet> tweets = parser.parseResults(results, symbol);
	std::string next = parser.parseNextPage(results);
	while (next.length() > 0) {
		url = buildNextSearchURL(next);
		results = curlRead(url);
		std::set<Tweet> nextTweets = parser.parseResults(results, symbol);
		tweets.insert(nextTweets.begin(), nextTweets.end());
		next = parser.parseNextPage(results);
	}

	return tweets;
}

std::string Twitter::buildInitialSearchURL(const std::string& symbol) {
	DBHandler dbh;
	std::stringstream strstream;
	strstream << dbh.getMostRecentID(symbol.c_str());
	std::string url = BASE_URL + std::string("?lang=en&rpp=100&q=%24") + symbol + std::string("&since_id=") + strstream.str();
	return url;
}

std::string Twitter::buildNextSearchURL(const std::string& next) {
	std::string url = BASE_URL + next;
	return url;
}

std::string Twitter::curlRead(const std::string& searchURL) {
	CURL* curl;
	std::string buffer;
	const char* url = searchURL.c_str();
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

int Twitter::curlWrite(char* data, size_t size, size_t len, std::string& buffer) {
	int result = 0;
	if (!buffer.empty()) {
		buffer.append(data, size * len);
		result = size * len;
	}
	return result;
}

