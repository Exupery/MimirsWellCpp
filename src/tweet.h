/*
 * tweet.h
 *
 *  Created on: Aug 19, 2012
 *      Author: frost
 */

#include <string>

#ifndef TWEET_H_
#define TWEET_H_

class Tweet {
friend bool operator<(const Tweet& a, const Tweet& b);
private:
	int userID;
	long id;
	long postedAt;
	std::string text;
	std::string symbol;
public:
	Tweet(const std::string &symbol);
	virtual ~Tweet();
	void setUserID(int userID);
	void setID(long id);
	void setPostedAt(long postedAt);
	void setText(std::string text);
	int getUserID();
	long getID() const;
	long getPostedAt();
	std::string getText();
	std::string getSymbol();
};

#endif /* TWEET_H_ */
