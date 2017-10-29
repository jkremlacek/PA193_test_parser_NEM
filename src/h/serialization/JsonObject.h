#pragma once

#include <string>
#include <map>

#include "JsonAttribute.h"

using namespace std;

class JsonObject
{
private:
	map<string, JsonAttribute> attributes;

public:
	void addAttribute(JsonAttribute attr);

	JsonAttribute getAttributeWithId(string id);

	int getAttributeCount();
};

