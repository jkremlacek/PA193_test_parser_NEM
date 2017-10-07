#pragma once

#include "Validatable.h"

class Key: public Validatable
{
public:
	Key();
	~Key();

	bool isValid() override;
};

