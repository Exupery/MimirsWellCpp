/*
 * parser.cpp
 *
 *  Created on: Aug 19, 2012
 *      Author: frost
 */

#include <algorithm>
#include <iostream> //DELME
#include <string>
#include <jansson.h>
#include <time.h>
#include "parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}

std::string parseNextPage(std::string json) {
	return "";
}

std::set<Tweet> Parser::parseResults(const std::string json) {
	std::set<Tweet> tweets;
	json_error_t error;
	json_t * root, * results;
	//remove newlines for jansson
	std::string str = json;
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
//	char * source = (char *)"{\"results\":[{\"created_at\":\"Sat, 18 Aug 2012 20:14:17 +0000\",\"from_user_id\":106725205,\"id\":236918965404848128,\"text\":\"testing...\"}]}";
	char * source = (char *)str.c_str();
	root = json_loads(source, 0, &error);
	if (root && json_is_object(root)) {
		std::cout << "It's an object!" << std::endl; //DELME
		results = json_object_get(root, "results");
		if (results && json_is_array(results)) {
			for (size_t i=0; i < json_array_size(results); i++) {
				json_t * data, * createdAt, * userID, * id, * text;
				data = json_array_get(results, i);
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

					if (t.getID() > 0 && t.getPostedAt() > 0) {
						tweets.insert(t);
					}
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
	long epoch;
	struct tm tm;
	char * buffer = (char *)timestamp.c_str();
	if (strptime(buffer, "%a, %d %b %Y %H:%M:%S", &tm) != NULL) {
		epoch = mktime(&tm);
		std::cout << epoch << std::endl; //DELME
	} else {
		epoch = 0;
	}

	return epoch;
}

