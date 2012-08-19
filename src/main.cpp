/*
+=======================================================+
|	Name        : Mimir's Well							|
|	Author      : Matthew Frost							|
|	Version     : 0.1									|
|	Copyright   : "BEER-WARE LICENSE"					|
|	Description : Stock Market Sentiment Analyzer		|
+=======================================================+
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include "twitter.h"
#include "tweet.h"

int main(int argc, char * argv[]) {
	std::cout << "testing tweet class" << std::endl;
	Twitter twitter;
	std::set<Tweet> test = twitter.search("QQQ");
	std::cout << test.size() << std::endl;

	return 0;
}
