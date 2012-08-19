/*
 * twitter.cpp
 *
 *  Created on: Aug 18, 2012
 *      Author: frost
 */

#include <iostream>
#include <string>
#include "twitter.h"

Twitter::Twitter() {
	std::string url = buildSearchURL("QQQ");
	std::cout << url << std::endl;
}

Twitter::~Twitter() {

}

std::string Twitter::buildSearchURL(std::string symbol) {
	std::string url = BASE_URL + std::string("?q=%24") + symbol;
	return url;
}

int Twitter::curlWrite(char * data, size_t size, size_t len, std::string * buffer) {
	int result = 0;
	if (buffer != NULL) {
		buffer->append(data, size * len);
		result = size * len;
	}
	return result;
}

