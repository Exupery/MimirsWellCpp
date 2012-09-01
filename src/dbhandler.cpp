/*
 * dbhandler.cpp
 *
 *  Created on: Sep 1, 2012
 *      Author: frost
 */

#include <iostream>
#include <mongo.h>
#include "dbhandler.h"

DBHandler::DBHandler() {
	std::cout << "testing...." << std::endl;	//DELME
	mongo conn;
	int status = mongo_connect(&conn, "127.0.0.1", 27017);
	if (status != MONGO_OK) {
		std::cerr << "Unable to connect to MONGODB\tError " << getMongoDBError(conn.err) << std::endl;	//DELME
	}
	bson b;
	bson_init(&b);
	bson_append_int(&b, "foo", 1811);
	bson_append_long(&b, "bar", 236932520988528640);
	bson_finish(&b);
	bson_print( &b );
	mongo_insert( &conn, "test.foo", &b, NULL );
	mongo_destroy(&conn);
}

DBHandler::~DBHandler() {

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

