#pragma once

#include <string>

#include "Validatable.h"

using namespace std;

class Key: public Validatable
{
	string hash;
public:
	Key() {};
	Key(string hash);
	~Key();

	string getHash();

	bool isValid() override;
};

