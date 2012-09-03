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
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include "dbhandler.h"
#include "twitter.h"
#include "tweet.h"

std::vector<std::string> getSymbols(int length, char * params[]);
void parseFromFile(std::string filename, std::vector<std::string> * symbols);
void parseFromArgs(int start, int end, char * syms[], std::vector<std::string> * symbols);

int main(int argc, char * argv[]) {
	time_t start = time(0);
	Twitter twitter;
	std::cout << "testing mongodb reads/writes\t" << start << std::endl;
	std::vector<std::string> symbols = getSymbols(argc, argv);
	std::vector<std::string>::const_iterator iter = symbols.begin();
	while (iter != symbols.end()) {
		std::cout << *iter << std::endl; //DELME
		iter++;
	}
	std::cout << "Total:\t" << symbols.size() << std::endl;


	std::vector<Tweet> test = twitter.search("QQQ");
	std::cout << test.size() << std::endl;

	DBHandler dbh;
	dbh.addTweets(&test);

	std::cout << "testing complete\t" << time(0) << "\t" << time(0)-start << "ms" << std::endl;
	return 0;
}

std::vector<std::string> getSymbols(int length, char * params[]) {
	std::vector<std::string> symbols;
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

void parseFromFile(std::string filename, std::vector<std::string> * symbols) {
	std::ifstream infile(filename.c_str());
	std::string line;
	while (std::getline(infile, line)) {
		symbols->push_back(line);
	}
}

void parseFromArgs(int start, int end, char * syms[], std::vector<std::string> * symbols) {
	for (int i=start; i<end; i++) {
		if (syms[i][0] == '-') {
			break;
		}
		symbols->push_back(syms[i]);
	}
}
