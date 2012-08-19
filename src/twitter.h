/*
 * twitter.h
 *
 *  Created on: Aug 18, 2012
 *      Author: frost
 */

#include <string>
#define BASE_URL "http://127.0.0.1/test.json"
//#define BASE_URL "http://search.twitter.com/search.json"
#ifndef TWITTER_H_
#define TWITTER_H_

class Twitter {
private:
	std::string buildSearchURL(std::string symbol);
	std::string curlRead(std::string url);
	int curlWrite(char * data, size_t size, size_t len, std::string * buffer);
public:
	Twitter();
	virtual ~Twitter();
};

#endif /* TWITTER_H_ */
