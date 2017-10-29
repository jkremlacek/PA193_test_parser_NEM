#pragma once

#include <string>
#include <map>

#include "JsonAttribute.h"

using namespace std;

class JsonObject
{
private:
	double id;
	map<string, JsonAttribute> attributes;

public:
	JsonObject(double id): id(id) {}

	void addAttribute(JsonAttribute attr);

	JsonAttribute getAttributeWithId(string id);

	int getAttributeCount();
};

