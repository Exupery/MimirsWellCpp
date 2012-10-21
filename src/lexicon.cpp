/*
 * lexicon.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: frost
 */
#include <iostream>	//DELME
#include <locale>
#include <string>
#include <sstream>
#include <algorithm>
#include "lexicon.h"

Lexicon::Lexicon() {


}

Lexicon::~Lexicon() {

}

void Lexicon::addWord(std::string& word) {
	std::locale loc;

	bool isValid = true;
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	if (word.substr(0, 7).compare("http://") == 0 || word.substr(0, 8).compare("https://") == 0) {
		isValid = false;
	}

	word.erase(std::remove_if(word.begin(), word.end(), isNotAlpha), word.end());

	if (word.length() < 2) {
		isValid = false;
	}

	if (isValid) {
		words.insert(word);
	}
}

bool Lexicon::isNotAlpha(char c) {
	return !(std::isalpha(c));
}

int Lexicon::parseTweet(const std::string& tweet) {
	int sizeBefore = words.size();
//	std::cout << tweet << std::endl;		//DELME
	std::string buffer;
	std::stringstream ss(tweet);

//	std::vector<std::string> tokens;

	while (ss >> buffer) {
//		tokens.push_back(buffer);
//		std::cout << buffer << std::endl;	//DELME
		addWord(buffer);
	}
	std::cout << words.size() << std::endl;	//DELME
	//TODO: add word (class) to set if not present
	//TODO: for each word add sym and timestamp
	return words.size() - sizeBefore;
}

std::set<std::string> Lexicon::getWords() {
	return words;
}
