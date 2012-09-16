/*
 * history.cpp
 *
 *  Created on: Sep 8, 2012
 *      Author: frost
 */

#include "curlio.h"
#include "history.h"
#include <iostream>
#include <sstream>


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
	while (std::getline(results, line)) {
		//skip header line(s)
		if (isdigit(line[0])) {
			//std::cout << line;
			size_t dateEnd = line.find_first_of(",");
			long date = getUNIXTime(line.substr(0, dateEnd));


			std::cout << line.substr(0, dateEnd) << "\t" << date << std::endl;	//DELME
		}
	}
	return true;
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

