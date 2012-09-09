/*
 * history.h
 *
 *  Created on: Sep 8, 2012
 *      Author: frost
 */

#include <set>
#include <string>

#define YAHOO_CSV_URL "http://ichart.yahoo.com/table.csv?g=d&a=7&b=1&c=2012&s="
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
