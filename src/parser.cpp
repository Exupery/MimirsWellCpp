/*
 * parser.cpp
 *
 *  Created on: Aug 19, 2012
 *      Author: frost
 */

#include <iostream> //DELME
#include <jansson.h>
#include "parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}

std::set<Tweet> Parser::parseJSON(const std::string json) {
	std::set<Tweet> tweets;
	json_error_t error;
	json_t * root, * data, * message;
	const char * message_text;
	char * text = (char *)"{\"created_at\":\"Sat, 18 Aug 2012 20:14:17 +0000\",\"from_user_id\":106725205,\"id\":236918965404848128,\"text\":\"testing...\"}";
//	char * text = (char *)json.c_str();
	root = json_loads(text, 0, &error);
	if (root) {
		Tweet t;
		tweets.insert(t);
		data = json_array_get(root, 0);
		message = json_object_get(data, "created_at");
		message_text = json_string_value(message);
		std::cout << message_text << std::endl;
	} else {
		std::cout << error.text << std::endl;
	}

	return tweets;
}

