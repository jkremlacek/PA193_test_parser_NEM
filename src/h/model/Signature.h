#pragma once

#include <string>

#include "Validatable.h"

using namespace std;

class Signature: public Validatable
{
	string hash;
public:
	Signature() {};
	Signature(string hash);
	~Signature();

	bool isValid() override;
};

