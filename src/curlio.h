/*
 * curlio.h
 *
 *  Created on: Sep 9, 2012
 *      Author: frost
 */

#include <string>
#include <curl/curl.h>
#include <curl/easy.h>

#ifndef CURLIO_H_
#define CURLIO_H_

class CurlIO {
public:
	CurlIO();
	virtual ~CurlIO();
	std::string curlRead(const std::string& url);
	static int curlWrite(char* data, size_t size, size_t len, std::string* buffer);
};

#endif /* CURLIO_H_ */
