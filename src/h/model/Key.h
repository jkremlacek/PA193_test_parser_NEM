#pragma once

#include <string>

#include "Validatable.h"

using namespace std;

class Key: public Validatable
{
	string hash;
public:
	Key(string hash);
	~Key();

	bool isValid() override;
};

