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
private:
	int userID;
	long id;
	long postedAt;
	std::string text;
public:
	Tweet();
	virtual ~Tweet();
	void setUserID(int userID);
	void setID(long id);
	void setPostedAt(long postedAt);
	void setText(std::string text);
	int getUserID();
	long getID();
	long getPostedAt();
	std::string getText();
};

#endif /* TWEET_H_ */
