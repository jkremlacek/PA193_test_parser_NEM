#pragma once

#include <string>
#include <vector>

using namespace std;

enum JsonAttributeType { STRING, NUMBER, BOOLEAN, ARRAY, SINGLE_OBJECT };

/*
	Represents JSON attribute values, not all attribute types specified
	in JSON specification are implemented (f.e. null)

	Dependent on attribute type is a subset of usable methods 
	(f.e cannot use getTextValue on number type)
*/
class JsonAttribute
{
private:
	JsonAttributeType jat;

	string name;
	string textValue;
	double numValue;
	bool boolValue;
	/*
		vector contains id keys of attached JsonObjects stored in JsonSerializer container
	*/
	vector<double> jsonValues;
public:
	JsonAttribute(JsonAttributeType jat, string name);

	const string getName();
	const JsonAttributeType getType();

	/*
		getter and setter usable on STRING attribute type
	*/
	void setTextValue(string text);
	const string getTextValue();

	/*
		getter and setter usable on NUMBER attribute type
	*/
	void setNumValue(string numValue);
	double getNumValue();

	/*
		getter and setter usable on BOOLEAN attribute type
	*/
	void setBoolValue(string boolValue);
	bool getBoolValue();

	/*
		getter and setter usable on ARRAY and SINGLE_OBJECT attribute type
		note that SINGLE_OBJECT can have only one object added via addJsonValue
	*/
	void addJsonValue(double joId);
	double getJsonValueAt(int i);
	int getJsonObjectCount();

	static JsonAttribute createBoolAttribute(string boolValue, string name);
	static JsonAttribute createNumAttribute(string numValue, string name);
};

