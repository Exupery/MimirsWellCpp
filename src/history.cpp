/*
 * history.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: frost
 */

#include "history.h"

History::History() {

}

History::~History() {

}

int History::updateHistoricalPrices(std::set<std::string> * symbols) {
	int fetched = 0;
	std::set<std::string>::const_iterator iter;
	iter = symbols->begin();
	while (iter!= symbols->end()) {
		std::string sym = *iter;
		if (getHistory(sym)) {
			fetched++;
		}
		iter++;
	}
	return fetched;
}

bool History::getHistory(const std::string & symbol) {

	return true;
}

