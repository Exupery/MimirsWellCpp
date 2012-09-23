/*
 * dbhandler.h
 *
 *  Created on: Sep 1, 2012
 *      Author: frost
 */
#include <set>
#include <mongo.h>
#include <map>
#include "tweet.h"

#define TWEETS "test.tweets"
#define PRICE_HISTORY "test.price_history"
//#define TWEETS "mimirswell.tweets"
//#define PRICE_HISTORY "mimirswell.price_history"

#ifndef DBHANDLER_H_
#define DBHANDLER_H_

class DBHandler {
private:
	std::string host;
	int port;
	bool connect(mongo& db);
	std::string getMongoDBError(int status);
	bool writeDocs(const bson** docs, const char* ns, int numDocs);
public:
	DBHandler();
	virtual ~DBHandler();
	bool addHistory(const std::map<long, double>& prices, const char* symbol);
	bool addTweets(const std::set<Tweet>& tweets);
	std::set<Tweet> getTweets();
	long getMostRecentID(const char* symbol);
};

#endif /* DBHANDLER_H_ */
