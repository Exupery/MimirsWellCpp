/*
 * parser.cpp
 *
 *  Created on: Aug 19, 2012
 *      Author: frost
 */

#include <jansson.h>
#include "parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}

std::set<Tweet> Parser::parseJSON(std::string json) {
	std::set<Tweet> tweets;
	json_error_t error;
	json_t * root;
	root = json_loads(json.c_str(), 0, &error);
	if (root) {
		Tweet t;
		tweets.insert(t);
	}
	return tweets;
}

