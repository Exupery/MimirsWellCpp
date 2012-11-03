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
	void addWord(std::set<std::string>& words, std::string& word);
	static bool isNotAlpha(char c);
public:
	Lexicon();
	virtual ~Lexicon();
	std::set<std::string> parseTweet(const std::string& tweet);
};

#endif /* LEXICON_H_ */
