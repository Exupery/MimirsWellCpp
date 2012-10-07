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
#define LEXICON "test.lexicon"
//#define TWEETS "mimirswell.tweets"
//#define PRICE_HISTORY "mimirswell.price_history"
//#define LEXICON "mimirswell.lexicon"

#ifndef DBHANDLER_H_
#define DBHANDLER_H_

class DBHandler {
private:
	std::string host;
	int port;
	bool connect(mongo& db);
	std::string getMongoDBError(int status);
	bool writeDocs(const bson** docs, const char* ns, int numDocs);
	long getLastLexiconUpdate();
	std::set<Tweet> getTweetsSince(long sinceTime);
public:
	DBHandler();
	virtual ~DBHandler();
	bool addHistory(const std::map<long, double>& prices, const char* symbol);
	bool addTweets(const std::set<Tweet>& tweets);
	long getMostRecentID(const char* symbol);
	std::set<Tweet> getTweets();
	std::set<std::string> getWords();
};

#endif /* DBHANDLER_H_ */
