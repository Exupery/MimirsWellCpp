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

//	mongo db;
//	bson query;
//	bson_init(&query);
//	bson_append_int(&query, "foo", 108);
//	bson_finish(&query);
//	runQuery(&db, &query, TWEETS);
//	mongo_destroy(&db);
//
//	std::cout << "\nALL:" << std::endl;
//	runQuery(&db, NULL, TWEETS);
//	mongo_destroy(&db);

}

DBHandler::~DBHandler() {

}

int DBHandler::addTweets(std::set<Tweet> * tweets) {
	int newDocs = 0;
	//TODO add tweets
//	std::vector<bson> tweetDocs;
//	bson tweetDocs[tweets->size()];
	const bson ** tweetDocs = (const bson **)malloc(sizeof(bson *) * tweets->size());
	std::set<Tweet>::const_iterator iter;
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
//		tweetDocs.push_back(b);
		tweetDocs[i++] = b;
		iter++;
	}
	newDocs = writeDocs(tweetDocs);
	std::cout << sizeof(tweetDocs[0]) << "\t" << sizeof(tweetDocs) / sizeof(tweetDocs[0]) << std::endl;	//DELME
	std::cout << newDocs << std::endl;	//DELME
	return newDocs;
}

int DBHandler::writeDocs(const bson ** docs) {
//int DBHandler::writeDocs(std::vector<bson> * docs) {
	mongo db;
	if (connect(&db)) {
//		mongo_write_concern * wr = db.write_concern;
		if (mongo_insert_batch(&db, "test.foo", docs, 15, db.write_concern, 0) != MONGO_OK) {
			std::cout << "unable to write to db" << std::endl;
		}
	//	std::cout << docs->size() << std::endl;	//DELME
		mongo_destroy(&db);
	} else {
		std::cout << "unable to connect" << std::endl;
	}
	return 0;
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

