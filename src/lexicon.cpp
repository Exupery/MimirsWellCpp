/*
 * lexicon.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: frost
 */

#include "lexicon.h"

Lexicon::Lexicon() {


}

Lexicon::~Lexicon() {

}

void Lexicon::addWord(std::string& word) {
	words.insert(word);
}

int Lexicon::parseTweet(const std::string& tweet) {
	int sizeBefore = words.size();


	return words.size() - sizeBefore;
}

std::set<std::string> Lexicon::getWords() {
	return words;
}
