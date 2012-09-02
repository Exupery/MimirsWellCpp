/*
 * dbhandler.cpp
 *
 *  Created on: Sep 1, 2012
 *      Author: frost
 */

#include <iostream>
#include "dbhandler.h"

DBHandler::DBHandler() {
	host = "127.0.0.1";
	port = 27017;
//	int status = mongo_connect(&db, "127.0.0.1", 27017);
//	if (status != MONGO_OK) {
//		std::cerr << "Unable to connect to MONGODB\tError " << getMongoDBError(db.err) << std::endl;	//DELME
//	}

//	bson b;
//	bson_init(&b);
//	bson_append_int(&b, "foo", 1811);
//	bson_append_long(&b, "bar", 236932520988528640);
//	bson_finish(&b);
//	bson_print( &b );
//	mongo_insert( &db, "test.test_tweets", &b, NULL );

	mongo db;
//	runQuery(&db, NULL, TWEETS);
	bson query;
	bson_init(&query);
	bson_append_int(&query, "foo", 108);
	bson_finish(&query);
	runQuery(&db, &query, TWEETS);
	mongo_destroy(&db);

	std::cout << "\nALL:" << std::endl;
	runQuery(&db, NULL, TWEETS);
	mongo_destroy(&db);
}

DBHandler::~DBHandler() {

}

int DBHandler::addTweets(std::set<Tweet>) {
	int newDocs = 0;

	return newDocs;
}

mongo_cursor DBHandler::runQuery(mongo * db, bson * query, const char * ns) {
	mongo_cursor cursor;
	if (connect(db)) {
		mongo_cursor_init (&cursor, db, ns);
		if (query != NULL) {
			mongo_cursor_set_query(&cursor, query);
		}
		while (mongo_cursor_next(&cursor) == MONGO_OK) {
			bson_print(&cursor.current);
		}
	}
	return cursor;
}

bool DBHandler::connect(mongo * db) {
	int status = mongo_connect(db, host.c_str(), port);
	if (status != MONGO_OK) {
		std::cerr << "Unable to connect to MONGODB\t" << getMongoDBError(db->err) << std::endl;
		return false;
	} else {
		return true;
	}
}

std::string DBHandler::getMongoDBError(int status) {
	std::string msg;
	switch (status) {
		case MONGO_CONN_SUCCESS:
			msg = "Connected";
			break;
		case MONGO_CONN_NO_SOCKET:
			msg = "No socket";
			break;
		case MONGO_CONN_FAIL:
			msg = "Connection failed";
			break;
		case MONGO_CONN_NOT_MASTER:
			msg = "Not master";
			break;
		default:
			msg = "Unknown status code";
			break;
	}
	return msg;
}

