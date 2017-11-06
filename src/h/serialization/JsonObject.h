#pragma once

#include <string>
#include <map>

#include "JsonAttribute.h"

using namespace std;
/*
	Represents JSON data structure encapsulated with curly brackets,
	contains map of named attributes
*/
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

	bool containsAttributeWithId(string id);
};

