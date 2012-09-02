/*
 * dbhandler.h
 *
 *  Created on: Sep 1, 2012
 *      Author: frost
 */
#include <set>
#include <mongo.h>
#include "tweet.h"

#define TWEETS "test.foo"

#ifndef DBHANDLER_H_
#define DBHANDLER_H_

class DBHandler {
private:
	std::string host;
	int port;
	bool connect(mongo * db);
	std::string getMongoDBError(int status);
	mongo_cursor runQuery(mongo * db, bson * query);
public:
	DBHandler();
	virtual ~DBHandler();
	int addTweets(std::set<Tweet>);
	std::set<Tweet> getTweets();
};

#endif /* DBHANDLER_H_ */
