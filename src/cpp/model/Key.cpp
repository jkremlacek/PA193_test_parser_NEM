#include "../../h/model/Key.h"


Key::Key(string hash)
{
	this->hash = hash;
}


Key::~Key()
{
}

bool Key::isValid() {
	return true;
}