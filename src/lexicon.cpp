/*
 * lexicon.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: frost
 */
#include <iostream>	//DELME
#include <string>
#include <sstream>
//#include <vector>
#include "lexicon.h"

Lexicon::Lexicon() {


}

Lexicon::~Lexicon() {

}

void Lexicon::addWord(std::string& word) {
	std::cout << word << std::endl;	//DELME
	//TODO: ignore urls
	//TODO: strip puncuation $ #
	//TODO: set min length >= 2
	//TODO: lowercase

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
