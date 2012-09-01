/*
 * dbhandler.h
 *
 *  Created on: Sep 1, 2012
 *      Author: frost
 */

#ifndef DBHANDLER_H_
#define DBHANDLER_H_

class DBHandler {
private:
	std::string getMongoDBError(int status);
public:
	DBHandler();
	virtual ~DBHandler();
};

#endif /* DBHANDLER_H_ */
