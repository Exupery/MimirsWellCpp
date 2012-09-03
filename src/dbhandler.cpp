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
}

DBHandler::~DBHandler() {

}

bool DBHandler::addTweets(std::vector<Tweet> * tweets) {
	const bson ** tweetDocs = (const bson **)malloc(sizeof(bson *) * tweets->size());
	std::vector<Tweet>::const_iterator iter;
	iter = tweets->begin();
	int i = 0;
	while (iter != tweets->end()) {
		Tweet t = *iter;
		bson * b = (bson *)malloc(sizeof(bson));
		bson_init(b);
		bson_append_int(b, "user_id", t.getUserID());
		bson_append_long(b, "id", t.getID());
		bson_append_long(b, "posted_at", t.getPostedAt());
		bson_append_string(b, "text", t.getText().c_str());
		bson_append_string(b, "sym", t.getSymbol().c_str());
		bson_finish(b);
		tweetDocs[i++] = b;
		iter++;
	}

	return writeDocs(tweetDocs);
}

bool DBHandler::writeDocs(const bson ** docs) {
	bool writeSuccess = false;
	mongo db;
	if (connect(&db)) {
		if (mongo_insert_batch(&db, "test.tweets", docs, 15, db.write_concern, 0) != MONGO_OK) {
			std::cerr << "Unable to write to MongoDB" << std::endl;
		} else {
			writeSuccess = true;
		}
		mongo_destroy(&db);
	}
	return writeSuccess;
}

long DBHandler::getLastPostedTime(const char * symbol) {
	long mostRecent = 0;
	//TODO get update time for sym
	return mostRecent;
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

