/*
 * curlio.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: frost
 */

#include "curlio.h"

CurlIO::CurlIO() {
}

CurlIO::~CurlIO() {

}

std::string CurlIO::curlRead(const std::string& searchURL) {
	CURL* curl;
	std::string buffer;
	const char* url = searchURL.c_str();
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWrite);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA,& buffer);

		curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	return buffer;
}

int CurlIO::curlWrite(char* data, size_t size, size_t len, std::string* buffer) {
	int result = 0;
	if (buffer != NULL) {
		buffer->append(data, size * len);
		result = size * len;
	}
	return result;
}

