/*
 * twitter.cpp
 *
 *  Created on: Aug 18, 2012
 *      Author: frost
 */

#include <iostream>
#include <sstream>
#include "curlio.h"
#include "dbhandler.h"
#include "twitter.h"
#include "parser.h"

Twitter::Twitter() {

}

Twitter::~Twitter() {

}

std::set<Tweet> Twitter::search(const std::string& symbol) {
	Parser parser;
	CurlIO curl;
	std::string url = buildInitialSearchURL(symbol);
	std::string results = curl.curlRead(url);
	std::set<Tweet> tweets = parser.parseResults(results, symbol);
	std::string next = parser.parseNextPage(results);
	while (next.length() > 0) {
		url = buildNextSearchURL(next);
		results = curl.curlRead(url);
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

