#pragma once

#include <string>
#include <vector>

using namespace std;

enum JsonAttributeType { STRING, NUMBER, BOOLEAN, ARRAY, SINGLE_OBJECT };

class JsonAttribute
{
private:
	JsonAttributeType jat;

	string name;
	string textValue;
	double numValue;
	bool boolValue;
	vector<double> jsonValues;
public:
	JsonAttribute(JsonAttributeType jat, string name);

	const string getName();
	const JsonAttributeType getType();

	void setTextValue(string text);
	const string getTextValue();

	void setNumValue(string numValue);
	double getNumValue();

	void setBoolValue(string boolValue);
	bool getBoolValue();

	void addJsonValue(double joId);
	double getJsonValueAt(int i);
	int getJsonObjectCount();

	static JsonAttribute createBoolAttribute(string boolValue, string name);
	static JsonAttribute createNumAttribute(string numValue, string name);
};

