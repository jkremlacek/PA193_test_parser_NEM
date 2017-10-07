#pragma once

#include "Validatable.h"

class Transaction: public Validatable
{
public:
	Transaction();
	~Transaction();

	bool isValid() override;
};

