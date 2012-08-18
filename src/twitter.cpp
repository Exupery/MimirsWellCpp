/*
 * Twitter.cpp
 *
 *  Created on: Aug 18, 2012
 *      Author: frost
 */

#include <iostream>
#include <string>
#include "twitter.h"

const std::string BASE_URL = "http://127.0.0.1/test.json";
//const std::string BASE_URL = "http://search.twitter.com/search.json?q=$QQQ";

Twitter::Twitter() {
	std::cout << BASE_URL << std::endl;
}

Twitter::~Twitter() {

}

