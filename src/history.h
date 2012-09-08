/*
 * history.h
 *
 *  Created on: Sep 8, 2012
 *      Author: frost
 */

#include <set>
#include <string>

#ifndef HISTORY_H_
#define HISTORY_H_

class History {
public:
	History();
	virtual ~History();
	int updateHistoricalPrices(std::set<std::string> * symbols);
};

#endif /* HISTORY_H_ */
