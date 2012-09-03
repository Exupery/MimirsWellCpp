/*
 * dbhandler.h
 *
 *  Created on: Sep 1, 2012
 *      Author: frost
 */
#include <vector>
#include <mongo.h>
#include "tweet.h"

#define TWEETS "test.tweets"

#ifndef DBHANDLER_H_
#define DBHANDLER_H_

class DBHandler {
private:
	std::string host;
	int port;
	bool connect(mongo * db);
	std::string getMongoDBError(int status);
	bool writeDocs(const bson ** docs, const char * ns, int numDocs);
public:
	DBHandler();
	virtual ~DBHandler();
	bool addTweets(std::vector<Tweet> * tweets);
	std::vector<Tweet> getTweets();
	long getMostRecentID(const char * symbol);
};

#endif /* DBHANDLER_H_ */
