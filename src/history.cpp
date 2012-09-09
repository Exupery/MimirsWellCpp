/*
 * history.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: frost
 */

#include "curlio.h"
#include "history.h"
#include <iostream>
History::History() {

}

History::~History() {

}

int History::updateHistoricalPrices(const std::set<std::string>& symbols) {
	int fetched = 0;
	std::set<std::string>::const_iterator iter;
	iter = symbols.begin();
	while (iter!= symbols.end()) {
		std::string sym = *iter;
		if (getHistory(sym)) {
			fetched++;
		}
		iter++;
	}
	return fetched;
}

bool History::getHistory(const std::string& symbol) {
	CurlIO curl;
	std::string url = YAHOO_CSV_URL + symbol;
	std::string results = curl.curlRead(url);
	std::cout << results;	//DELME
	//TODO: parse history
	return true;
}

