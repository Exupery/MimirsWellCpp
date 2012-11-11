/*
 * dbhandler.cpp
 *
 *  Created on: Sep 1, 2012
 *      Author: frost
 */

#include <iostream>
#include "dbhandler.h"
#include "lexicon.h"

DBHandler::DBHandler() {
	host = "127.0.0.1";
	port = 27017;
}

DBHandler::~DBHandler() {

}

bool DBHandler::addTweets(const std::set<Tweet>& tweets) {
	const bson** tweetDocs = (const bson**)malloc(sizeof(bson*) * tweets.size());
	std::set<Tweet>::const_iterator iter;
	int i = 0;
	for (iter = tweets.begin(); iter != tweets.end(); iter++) {
		Tweet t = *iter;
		bson* b = (bson*)malloc(sizeof(bson));
		bson_init(b);
		bson_append_int(b, "user_id", t.getUserID());
		bson_append_long(b, "id", t.getID());
		bson_append_long(b, "posted_at", t.getPostedAt());
		bson_append_string(b, "text", t.getText().c_str());
		bson_append_string(b, "sym", t.getSymbol().c_str());
		bson_finish(b);
		tweetDocs[i++] = b;
	}

	return writeDocs(tweetDocs, TWEETS, i);
}


bool DBHandler::addHistory(const std::map<long, double>& prices, const char* symbol) {
	const bson** histDocs = (const bson**)malloc(sizeof(bson*) * prices.size());
	std::map<long, double>::const_iterator iter;
	int i = 0;
	for (iter = prices.begin(); iter != prices.end(); iter++) {
		bson* b = (bson*)malloc(sizeof(bson));
		bson_init(b);
		bson_append_string(b, "sym", symbol);
		bson_append_long(b, "timestamp", iter->first);
		bson_append_double(b, "close", iter->second);
		bson_finish(b);
		histDocs[i++] = b;
	}

	return writeDocs(histDocs, PRICE_HISTORY, i);
}

int DBHandler::addWords() {
	long sinceTime = getLastLexiconUpdate();
	std::vector<Word> words = parseTweets(sinceTime);
	mongo db;
	if (connect(db)) {
		std::vector<Word>::const_iterator iter;
		for (iter=words.begin(); iter!=words.end(); iter++) {
			Word w = *iter;
			bson doc, timestamps;
			bson_init(&doc);
			bson_append_string(&doc, "word", w.getWord().c_str());
			bson_finish(&doc);

			bson_init(&timestamps);
			bson_append_start_object(&timestamps, "$push");

			bson_append_start_object(&timestamps, "timestamps");
			bson_append_long(&timestamps, "time", w.getTimestamp());
			bson_append_string(&timestamps, "sym", w.getSymbol().c_str());
			bson_append_long(&timestamps, "tweet_id", w.getTweetID());
			bson_append_finish_object(&timestamps);

			bson_append_finish_object(&timestamps);
			bson_finish(&timestamps);

			mongo_update(&db, LEXICON, &doc, &timestamps, MONGO_UPDATE_UPSERT, db.write_concern);

//			coll.update({"word":"alcoa"},{$push:{"timestamps":{"time":2000,"sym":"ABC"}}},{upsert:true})
//			coll.find({timestamps:{$elemMatch:{"time":{$gt:1000}}}})
//			coll.find({timestamps:{$elemMatch:{"sym":"KJB"}}})
		}
	}
	mongo_destroy(&db);
	return words.size();
}

void DBHandler::addWordIfNotPresent(const std::string& word) {	//DELME???
	std::cout<<word<<std::endl;
}

long DBHandler::getMostRecentID(const char* symbol) {
	long mostRecent = 0;
	mongo db;
	if (connect(db)){
		mongo_cursor cursor;
		mongo_cursor_init(&cursor, &db, TWEETS);

		bson query;
		bson_init(&query);
		bson_append_start_object(&query, "$query");
		bson_append_string(&query, "sym", symbol);
		bson_append_finish_object(&query);
		bson_append_start_object(&query, "$orderby");
		bson_append_int(&query, "posted_at", -1);
		bson_append_finish_object(&query);
		bson_finish(&query);

		mongo_cursor_set_query(&cursor, &query);
		cursor.limit = 1;
		while (mongo_cursor_next(&cursor) == MONGO_OK) {
			bson_iterator iter;
			if (bson_find(&iter, mongo_cursor_bson(&cursor), "id")) {
				mostRecent = bson_iterator_long(&iter);
			}
		}
		mongo_cursor_destroy(&cursor);
	}
	mongo_destroy(&db);
	return mostRecent;
}

std::vector<Word> DBHandler::parseTweets(long sinceTime) {
	mongo db;
	Lexicon lex;
	std::vector<Word> words;
		if (connect(db)) {
			mongo_cursor cursor;
			mongo_cursor_init(&cursor, &db, TWEETS);
			bson query;
			bson_init(&query);
			bson_append_start_object(&query, "posted_at");
			bson_append_long(&query, "$gt", sinceTime);
			bson_append_finish_object(&query);
			bson_finish(&query);
			cursor.limit = 10;				//DELME
			mongo_cursor_set_query(&cursor, &query);
			while (mongo_cursor_next(&cursor) == MONGO_OK) {
				bson_iterator iter;
				std::set<std::string> wordsInTweet;
				std::string sym;
				long timestamp;

				if (bson_find(&iter, mongo_cursor_bson(&cursor), "text")) {
//					std::cout << bson_iterator_string(&iter) << std::endl;	//DELME
					wordsInTweet = lex.parseTweet(bson_iterator_string(&iter));
				} else {
					continue;
				}

				if (bson_find(&iter, mongo_cursor_bson(&cursor), "sym")) {
					sym = bson_iterator_string(&iter);
//					std::cout << sym << std::endl;		//DELME
				} else {
					continue;
				}

				if (bson_find(&iter, mongo_cursor_bson(&cursor), "posted_at")) {
					timestamp = bson_iterator_long(&iter);
//					std::cout << timestamp << std::endl;//DELME
				} else {
					continue;
				}

				std::set<std::string>::const_iterator w = wordsInTweet.begin();
				while (w != wordsInTweet.end()) {
					std::cout << *w << std::endl;		//DELME
					Word word(*w);
					word.setSymbol(sym);
					word.setTimestamp(timestamp);
					words.push_back(word);
					w++;
				}

			}
			mongo_cursor_destroy(&cursor);
		}
		mongo_destroy(&db);
	return words;
}

long DBHandler::getLastLexiconUpdate() {
	long lastUpdate = 0;
	mongo db;
	if (connect(db)) {
		mongo_cursor cursor;
		mongo_cursor_init(&cursor, &db, LEXICON);
		bson query;
		bson_init(&query);
		bson_append_start_object(&query, "$query");
		bson_append_bool(&query, "last_update", 1);
		bson_append_finish_object(&query);
		bson_finish(&query);

		mongo_cursor_set_query(&cursor, &query);
		cursor.limit = 1;
		while (mongo_cursor_next(&cursor) == MONGO_OK) {
			bson_iterator iter;
			if (bson_find(&iter, mongo_cursor_bson(&cursor), "last_update")) {
				lastUpdate = bson_iterator_long(&iter);
			}
		}
		mongo_cursor_destroy(&cursor);
	}
	mongo_destroy(&db);
	return lastUpdate;
}

bool DBHandler::writeDocs(const bson** docs, const char* ns, int numDocs) {
	bool writeSuccess = false;
	mongo db;
	if (connect(db)) {
		if (mongo_insert_batch(&db, ns, docs, numDocs, db.write_concern, 0) != MONGO_OK) {
			std::cerr << "Unable to write to MongoDB" << std::endl;
		} else {
			writeSuccess = true;
		}

	}
	mongo_destroy(&db);
	return writeSuccess;
}

bool DBHandler::connect(mongo& db) {
	int status = mongo_connect(&db, host.c_str(), port);
	if (status != MONGO_OK) {
		std::cerr << "Unable to connect to MONGODB\t" << getMongoDBError(db.err) << std::endl;
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

