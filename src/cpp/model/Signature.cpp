#include "..\..\h\model\Signature.h"


Signature::Signature(string hash)
{
	this->hash = hash;
}


Signature::~Signature()
{
}

bool Signature::isValid() {
	//TODO: implement validation
	return true;
}