/*
 * parser.h
 *
 *  Created on: Aug 19, 2012
 *      Author: frost
 */
#include <set>
#include<string>
#include "tweet.h"
#ifndef PARSER_H_
#define PARSER_H_

class Parser {
private:
	long getUNIXTime(std::string timestamp);
public:
	Parser();
	virtual ~Parser();
	std::string parseNextPage(std::string json);
	std::set<Tweet> parseResults(std::string json);
};

#endif /* PARSER_H_ */
