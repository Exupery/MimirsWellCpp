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
	json_t * root;
	json_t * data, * createdAt, * userID, * id, * text;
	char * source = (char *)"[{\"created_at\":\"Sat, 18 Aug 2012 20:14:17 +0000\",\"from_user_id\":106725205,\"id\":236918965404848128,\"text\":\"testing...\"}]";
//	char * source = (char *)json.c_str();
	root = json_loads(source, 0, &error);
	if (root) {
		Tweet t;
		tweets.insert(t);
		if (json_is_array(root)) {
			for (size_t i=0; i < json_array_size(root); i++) {
//				json_t * data, * createdAt, * userID, * id, * text;
//				const char * message_text;
				data = json_array_get(root, i);
				if (json_is_object(data)) {
					createdAt = json_object_get(data, "created_at");
					userID = json_object_get(data, "from_user_id");
					id = json_object_get(data, "id");
					text = json_object_get(data, "text");
				}
			}
			std::cout << json_string_value(createdAt) << std::endl;
			std::cout << json_number_value(userID) << std::endl;
			std::cout << json_number_value(id) << std::endl;
			std::cout << json_string_value(text) << std::endl;
		} else {
			std::cout << "JSON array expected!" << std::endl;
		}
	} else {
		std::cout << error.text << std::endl;
	}

	return tweets;
}

