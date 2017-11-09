#include "..\..\h\model\Signature.h"


Signature::Signature(string hash) {
	this->hash = hash;
}

Signature::~Signature() {}

string Signature::getHash() {
	return this->hash;
}

bool Signature::isValid() {
	//TODO: implement validation
	return true;
}