#pragma once

#include <string>
#include <vector>

#include "JsonObject.h"

using namespace std;

enum JsonAttributeType {STRING, ARRAY, SINGLE_OBJECT};

class JsonAttribute
{
private:
	JsonAttributeType jat;

	string name;
	string textValue;
	vector<JsonObject> jsonValues;
public:
	JsonAttribute(JsonAttributeType jat, string name) : jat(jat), name(name) {
		if (name.length() == 0) throw new exception("Json attribute name cannot be empty.");
	}

	const string getName();
	const JsonAttributeType getType();

	void setTextValue(string text);
	const string getTextValue();

	void addJsonValue(JsonObject jo);
	const JsonObject getJsonValueAt(int i);
	int getJsonObjectCount();
};

