#include "../../h/model/Key.h"


Key::Key(string hash)
{
	this->hash = hash;
}


Key::~Key()
{
}

bool Key::isValid() {
	//TODO: implement validation
	return true;
}