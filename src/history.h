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
private:
	bool getHistory(const std::string& symbol);
public:
	History();
	virtual ~History();
	int updateHistoricalPrices(const std::set<std::string>& symbols);
};

#endif /* HISTORY_H_ */