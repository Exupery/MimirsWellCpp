/*
+=======================================================+
|	Name        : Mimir's Well							|
|	Author      : Matthew Frost							|
|	Version     : 0.1									|
|	Copyright   : "BEER-WARE LICENSE"					|
|	Description : Stock Market Sentiment Analyzer		|
+=======================================================+
*/

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include "twitter.h"
#include "tweet.h"

std::set<std::string> getSymbols(int length, char * params[]);
void parseFromFile(std::string filename, std::set<std::string> * symbols);
void parseFromArgs(int start, int end, char * syms[], std::set<std::string> * symbols);

int main(int argc, char * argv[]) {
	std::cout << "testing mongodb writes" << std::endl;

	std::set<std::string> symbols = getSymbols(argc, argv);

	std::set<std::string>::const_iterator iter = symbols.begin();
	while (iter != symbols.end()) {
		std::cout << *iter << std::endl; //DELME
		iter++;
	}
	std::cout << "Total:\t" << symbols.size() << std::endl;

	Twitter twitter;
	std::set<Tweet> test = twitter.search("QQQ");
	std::cout << test.size() << std::endl;

	DBHandler dbh;

	return 0;
}

std::set<std::string> getSymbols(int length, char * params[]) {
	std::set<std::string> symbols;
	int c;
		while ((c = getopt(length, params, "f:s:")) != -1) {
			switch (c) {
			case 'f':
				parseFromFile(optarg, &symbols);
				break;
			case 's':
				parseFromArgs(optind-1, length, params, &symbols);
				break;
			default:
				break;
			}
		}
	return symbols;
}

void parseFromFile(std::string filename, std::set<std::string> * symbols) {
	std::ifstream infile(filename.c_str());
	std::string line;
	while (std::getline(infile, line)) {
		symbols->insert(line);
	}
}

void parseFromArgs(int start, int end, char * syms[], std::set<std::string> * symbols) {
	for (int i=start; i<end; i++) {
		if (syms[i][0] == '-') {
			break;
		}
		symbols->insert(syms[i]);
	}
}
