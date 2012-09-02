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
	bool connect(mongo * db);
	std::string getMongoDBError(int status);
public:
	DBHandler();
	virtual ~DBHandler();
	int addTweets(std::set<Tweet>);
};

#endif /* DBHANDLER_H_ */
