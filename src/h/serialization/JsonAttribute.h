#pragma once

#include <string>
#include <vector>

using namespace std;

enum JsonAttributeType { STRING, ARRAY, SINGLE_OBJECT };

class JsonAttribute
{
private:
	JsonAttributeType jat;

	string name;
	string textValue;
	vector<double> jsonValues;
public:
	JsonAttribute(JsonAttributeType jat, string name);

	const string getName();
	const JsonAttributeType getType();

	void setTextValue(string text);
	const string getTextValue();

	void addJsonValue(double joId);
	double getJsonValueAt(int i);
	int getJsonObjectCount();
};

