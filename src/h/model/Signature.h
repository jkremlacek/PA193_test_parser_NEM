#pragma once

#include "Validatable.h"

class Signature: public Validatable
{
public:
	Signature();
	~Signature();

	bool isValid() override;
};

