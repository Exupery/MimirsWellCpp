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
public:
	Parser();
	virtual ~Parser();
	std::set<Tweet> parseJSON(std::string json);
};

#endif /* PARSER_H_ */
