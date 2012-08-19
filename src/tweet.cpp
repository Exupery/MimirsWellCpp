/*
 * tweet.cpp
 *
 *  Created on: Aug 19, 2012
 *      Author: frost
 */

#include "tweet.h"

Tweet::Tweet() {
	userID = 0;
	id = 0;
	postedAt = 0;
	text = "";
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

void Tweet::setText(std::string text) {
	this->text = text;
}

int Tweet::getUserID() {
	return userID;
}

long Tweet::getID() {
	return id;
}

long Tweet::getPostedAt() {
	return postedAt;
}

std::string Tweet::getText() {
	return text;
}

