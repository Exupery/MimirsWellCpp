/*
 * lexicon.h
 *
 *  Created on: Oct 14, 2012
 *      Author: frost
 */

#include <set>
#include <string>
#ifndef LEXICON_H_
#define LEXICON_H_

class Lexicon {
private:
	std::set<std::string> words;
	void addWord(std::string& word);
public:
	Lexicon();
	virtual ~Lexicon();
	int parseTweet(const std::string& tweet);
	std::set<std::string> getWords();
};

#endif /* LEXICON_H_ */
