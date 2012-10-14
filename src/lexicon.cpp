/*
 * lexicon.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: frost
 */
#include <iostream>	//DELME
#include <string>
#include <sstream>
#include <algorithm>
#include "lexicon.h"

Lexicon::Lexicon() {


}

Lexicon::~Lexicon() {

}

void Lexicon::addWord(std::string& word) {
	const char* old = word.c_str();	//DELME

	bool isValid = true;
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	if (word.substr(0, 7).compare("http://") == 0 || word.substr(0, 8).compare("https://") == 0) {
		isValid = false;
	} else if (word.length() < 2) {
		isValid = false;
	}
	//TODO: strip non alphanumeric

	if (isValid) {
		std::cout << old << "\t\t" << word << std::endl;	//DELME
	}

	words.insert(word);
}

int Lexicon::parseTweet(const std::string& tweet) {
	int sizeBefore = words.size();
//	std::cout << tweet << std::endl;	//DELME
	std::string buffer;
	std::stringstream ss(tweet);

//	std::vector<std::string> tokens;

	while (ss >> buffer) {
//		tokens.push_back(buffer);
//		std::cout << buffer << std::endl;	//DELME
		addWord(buffer);
	}

	return words.size() - sizeBefore;
}

std::set<std::string> Lexicon::getWords() {
	return words;
}
