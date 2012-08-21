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
	char * source = (char *)"[{\"created_at\":\"Sat, 18 Aug 2012 20:14:17 +0000\",\"from_user_id\":106725205,\"id\":236918965404848128,\"text\":\"testing...\"}]";
//	char * source = (char *)json.c_str();
	root = json_loads(source, 0, &error);
	if (root) {
		if (json_is_array(root)) {
			for (size_t i=0; i < json_array_size(root); i++) {
				json_t * data, * createdAt, * userID, * id, * text;
				data = json_array_get(root, i);
				if (json_is_object(data)) {
					Tweet t;

					createdAt = json_object_get(data, "created_at");
					if (json_is_string(createdAt)) {
						t.setPostedAt(getUNIXTime(json_string_value(createdAt)));
					}

					userID = json_object_get(data, "from_user_id");
					if (json_is_number(userID)) {
						t.setUserID((long)json_number_value(userID));
					}

					id = json_object_get(data, "id");
					if (json_is_number(id)) {
						t.setID((long)json_number_value(id));
					}

					text = json_object_get(data, "text");
					if (json_is_string(text)) {
						t.setText(json_string_value(text));
					}

					tweets.insert(t);
				}
			}
		} else {
			std::cout << "JSON array expected!" << std::endl;
		}
	} else {
		std::cout << error.text << std::endl;
	}

	return tweets;
}

long Parser::getUNIXTime(std::string timestamp) {
	//TODO: parse timestamp && convert to long
	return 0L;
}

