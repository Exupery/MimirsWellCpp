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
#include <unistd.h>
#include "twitter.h"
#include "tweet.h"

std::set<std::string> getSymbols(int length, char * params[]);

int main(int argc, char * argv[]) {
	std::cout << "parsing argv for symbols" << std::endl;
	std::cout << argc << std::endl;	//DELME

	std::set<std::string> symbols = getSymbols(argc, argv);
	std::cout << "Symbols:\t" << symbols.size() << std::endl;

//	Twitter twitter;
//	std::set<Tweet> test = twitter.search("QQQ");
//	std::cout << test.size() << std::endl;

	return 0;
}

std::set<std::string> getSymbols(int length, char * params[]) {
	std::set<std::string> symbols;
	int c;
		while ((c = getopt(length, params, "f:s:")) != -1) {
			switch (c) {
			case 'f':
				std::cout << "f" << "\t" << optind << "\t" << optarg << std::endl;
				break;
			case 's':
				std::cout << "s" << "\t" << optind << "\t" << optarg << std::endl;
				break;
			default:
				std::cout << c << optarg << std::endl;
				break;
			}
		}
	return symbols;
}
