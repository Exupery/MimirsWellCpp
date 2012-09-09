/*
 * twitter.h
 *
 *  Created on: Aug 18, 2012
 *      Author: frost
 */

#include <set>
#include <string>
#include "tweet.h"

//#define BASE_URL "http://127.0.0.1/test.json"
#define BASE_URL "http://search.twitter.com/search.json"
#ifndef TWITTER_H_
#define TWITTER_H_

class Twitter {
private:
	std::string buildInitialSearchURL(const std::string& symbol);
	std::string buildNextSearchURL(const std::string& next);
public:
	Twitter();
	virtual ~Twitter();
	std::set<Tweet> search(const std::string& symbol);
};

#endif /* TWITTER_H_ */
