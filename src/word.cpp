/*
 * word.cpp
 *
 *  Created on: Nov 3, 2012
 *      Author: frost
 */

#include "word.h"

Word::Word(std::string word) : word(word) {
	timestamp = 0L;
	tweetID = 0L;
	symbol = "";
}

Word::~Word() {

}

std::string Word::getWord() const {
	return word;
}

std::string Word::getSymbol() {
	return symbol;
}

long Word::getTimestamp() {
	return timestamp;
}

long Word::getTweetID() {
	return tweetID;
}

void Word::setSymbol(std::string symbol) {
	this->symbol = symbol;
}

void Word::setTimestamp(long timestamp) {
	this->timestamp = timestamp;
}

void Word::setTweetID(long tweetID) {
	this->tweetID = tweetID;
}

