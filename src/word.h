/*
 * word.h
 *
 *  Created on: Nov 3, 2012
 *      Author: frost
 */

#include <string>

#ifndef WORD_H_
#define WORD_H_

class Word {
	friend bool operator<(const Word& a, const Word& b);
private:
	std::string word;
	std::string symbol;
	long timestamp;
public:
	Word(std::string word);
	virtual ~Word();
	std::string getWord() const;
	std::string getSymbol();
	void setSymbol(std::string symbol);
	long getTimestamp();
	void setTimestamp(long timestamp);
};

#endif /* WORD_H_ */
