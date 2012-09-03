/*
 * dbhandler.h
 *
 *  Created on: Sep 1, 2012
 *      Author: frost
 */
#include <set>
#include <vector>
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
	mongo_cursor runQuery(mongo * db, bson * query, const char * ns);
//	int writeDocs(std::vector<bson> * docs);
	int writeDocs(const bson ** docs);
public:
	DBHandler();
	virtual ~DBHandler();
	int addTweets(std::set<Tweet> * tweets);
	std::set<Tweet> getTweets();
	long getLastPostedTime(const char * symbol);
};

#endif /* DBHANDLER_H_ */
