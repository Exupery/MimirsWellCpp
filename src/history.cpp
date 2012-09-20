/*
 * history.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: frost
 */

#include <iostream>
#include <map>
#include <sstream>
#include "curlio.h"
#include "dbhandler.h"
#include "history.h"

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
	std::string csv = curl.curlRead(url);
	std::stringstream results(csv, std::stringstream::in);
	std::string line;
	DBHandler dbh;
	std::map<long, double> prices;
	while (std::getline(results, line)) {
		//skip header line(s)
		if (isdigit(line[0])) {
			size_t dateEnd = line.find_first_of(",");
			long date = getUNIXTime(line.substr(0, dateEnd));
			size_t priceStart = line.find_last_of(",") + 1;
			double price = atof(line.substr(priceStart, std::string::npos).c_str());
			prices.insert(std::make_pair(date, price));
		}
	}

	if (prices.size() > 0) {
		return dbh.addHistory(prices);
	} else {
		return false;
	}
}

long History::getUNIXTime(const std::string& date) {
	long epoch;
	struct tm tm;
	std::string timestamp = date + "-21:00:00";
	char* buffer = (char*)timestamp.c_str();
	if (strptime(buffer, "%Y-%m-%d-%H:%M:%S", &tm) != NULL) {
		epoch = mktime(&tm);
	} else {
		epoch = 0;
	}

	return epoch;
}

