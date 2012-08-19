/*
 * twitter.h
 *
 *  Created on: Aug 18, 2012
 *      Author: frost
 */

#include <string>
#define BASE_URL "http://127.0.0.1/test.json?lang=en"
//#define BASE_URL "http://search.twitter.com/search.json?lang=en"
#ifndef TWITTER_H_
#define TWITTER_H_

class Twitter {
private:
	std::string buildSearchURL(std::string symbol);
	std::string curlRead(std::string url);
	static int curlWrite(char * data, size_t size, size_t len, std::string * buffer);
public:
	Twitter();
	virtual ~Twitter();
	std::string search(std::string symbol);
};

#endif /* TWITTER_H_ */
