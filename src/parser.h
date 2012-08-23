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
	long getUNIXTime(const std::string &timestamp);
public:
	Parser();
	virtual ~Parser();
	std::string parseNextPage(const std::string &json);
	std::set<Tweet> parseResults(const std::string &json);
};

#endif /* PARSER_H_ */
