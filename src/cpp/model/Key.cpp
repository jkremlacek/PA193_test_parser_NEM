#include "../../h/model/Key.h"

Key::Key(string hash) {
	this->hash = hash;
}

Key::~Key() {}

string Key::getHash() {
	return this->hash;
}

bool Key::isValid() {
	return true;
}