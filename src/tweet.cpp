/*
 * tweet.cpp
 *
 *  Created on: Aug 19, 2012
 *      Author: frost
 */

#include "tweet.h"

Tweet::Tweet(const std::string& symbol) {
	userID = 0;
	id = 0;
	postedAt = 0;
	text = "";
	this->symbol = symbol;
}

Tweet::~Tweet() {

}

void Tweet::setUserID(int userID) {
	this->userID = userID;
}

void Tweet::setID(long id) {
	this->id = id;
}

void Tweet::setPostedAt(long postedAt) {
	this->postedAt = postedAt;
}

void Tweet::setText(const char* text) {
	this->text = text;
}

int Tweet::getUserID() {
	return userID;
}

long Tweet::getID() const {
	return id;
}

long Tweet::getPostedAt() {
	return postedAt;
}

std::string Tweet::getSymbol() {
	return symbol;
}

std::string Tweet::getText() {
	return text;
}

bool operator<(const Tweet& a, const Tweet& b) {
	return (a.getID() < b.getID());
}

