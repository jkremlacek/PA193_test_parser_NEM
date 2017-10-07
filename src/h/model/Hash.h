#pragma once

#include <string>

#include "Validatable.h"

class Hash: public Validatable
{
private:
	std::string data;
public:
	Hash();
	~Hash();

	bool isValid() override;
};

