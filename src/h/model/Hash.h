#pragma once

#include <string>

#include "Validatable.h"

using namespace std;

class Hash: public Validatable
{
private:
	std::string data;
public:
	Hash(string data);
	~Hash();

	bool isValid() override;
};

