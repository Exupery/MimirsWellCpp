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
#include <iomanip>
#include <string>
#include <set>
#include <stdio.h>
#include <unistd.h>
#include "dbhandler.h"
#include "history.h"
#include "twitter.h"
#include "tweet.h"

std::set<std::string> getSymbols(int length, char* params[]);
int getTweets(std::set<std::string>& symbols);
void parseFromFile(std::string filename, std::set<std::string>& symbols);
void parseFromArgs(int start, int end, char* syms[], std::set<std::string>& symbols);

int main(int argc, char* argv[]) {
	time_t start = time(0);
	std::cout << std::left << std::setw(12) << "begin test" << start << std::endl;	//DELME
	std::set<std::string> symbols = getSymbols(argc, argv);
	std::cout << std::setw(12) << "Symbols:" << symbols.size() << std::endl;
//	int total = getTweets(symbols);
//	std::cout << std::setw(12) << "Tweets:" << total << std::endl;
	std::cout << "Retreiving historical price data...";
	History h;
	int fetched = h.updateHistoricalPrices(symbols);
	std::cout << "...complete" << std::endl;
	std::cout << "Obtained historical prices for " << fetched << " symbols" << std::endl;

	std::cout << std::setw(12) << "complete" << time(0) << "\t" << time(0)-start << "s" << std::endl;	//DELME
	return 0;
}

std::set<std::string> getSymbols(int length, char* params[]) {
	std::set<std::string> symbols;
	int c;
		while ((c = getopt(length, params, "f:s:")) != -1) {
			switch (c) {
			case 'f':
				parseFromFile(optarg, symbols);
				break;
			case 's':
				parseFromArgs(optind-1, length, params, symbols);
				break;
			default:
				break;
			}
		}
	return symbols;
}

void parseFromFile(std::string filename, std::set<std::string>& symbols) {
	std::ifstream infile(filename.c_str());
	std::string line;
	while (std::getline(infile, line)) {
		symbols.insert(line);
	}
}

void parseFromArgs(int start, int end, char* syms[], std::set<std::string>& symbols) {
	for (int i=start; i<end; i++) {
		if (syms[i][0] == '-') {
			break;
		}
		symbols.insert(syms[i]);
	}
}

int getTweets(std::set<std::string>& symbols) {
	int total = 0;
	DBHandler dbh;
	Twitter twitter;
	std::set<std::string>::const_iterator iter = symbols.begin();
	while (iter != symbols.end()) {
		std::set<Tweet> tweets = twitter.search((*iter).c_str());
		dbh.addTweets(tweets);
		std::cout << *iter << ":\t" << tweets.size() << std::endl;
		total += tweets.size();
		iter++;
	}
	return total;
}
