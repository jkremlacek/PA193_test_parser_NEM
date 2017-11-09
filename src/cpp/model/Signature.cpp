#include "..\..\h\model\Signature.h"


Signature::Signature(string hash)
{
	this->hash = hash;
}


Signature::~Signature()
{
}

bool Signature::isValid() {
	return true;
}