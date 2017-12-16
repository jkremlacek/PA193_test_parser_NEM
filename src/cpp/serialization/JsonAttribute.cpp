#include "../../h/serialization/JsonAttribute.h"

JsonAttribute::JsonAttribute(JsonAttributeType jat, string name): jat(jat), name(name) {
	if (name.length() == 0) throw runtime_error("Json attribute name cannot be empty.");
}

const string JsonAttribute::getName()
{
	return name;
}

const JsonAttributeType JsonAttribute::getType()
{
	return jat;
}

void JsonAttribute::setTextValue(string text)
{
	if (jat != JsonAttributeType::STRING)
	{
		throw runtime_error("Text value can be set only to STRING type JsonAttribute.");
	}

	textValue = text;
}

const string JsonAttribute::getTextValue()
{
	if (jat != JsonAttributeType::STRING)
	{
		throw runtime_error("Only STRING type JsonAttribute contains text value.");
	}

	return textValue;
}

void JsonAttribute::setNumValue(string numValue)
{
	if (jat != JsonAttributeType::NUMBER)
	{
		throw runtime_error("Only NUMBER type JsonAttribute contains numeric value.");
	}

	if (numValue.find_first_not_of(".1234567890") != string::npos || numValue.find_first_of(".") != numValue.find_last_of("."))
	{
		throw runtime_error("Invalid NUMBER value: " + numValue);
	}

	try {
		this->numValue = stod(numValue);
	}
	catch (std::out_of_range& exc) {
		throw runtime_error("Number out of double type range.");
	}
}

double JsonAttribute::getNumValue()
{
	if (jat != JsonAttributeType::NUMBER)
	{
		throw runtime_error("Only NUMBER type JsonAttribute contains numeric value.");
	}

	return numValue;
}

void JsonAttribute::setBoolValue(string boolValue)
{
	if (jat != JsonAttributeType::BOOLEAN)
	{
		throw runtime_error("Only BOOLEAN type JsonAttribute contains bool value.");
	}

	if (boolValue == "true")
	{
		this->boolValue = true;
	}
	else if (boolValue == "false") 
	{
		this->boolValue = false;
	}
	else {
		throw runtime_error("Invalid BOOLEAN type value." + boolValue);
	}
}

bool JsonAttribute::getBoolValue()
{
	if (jat != JsonAttributeType::BOOLEAN)
	{
		throw runtime_error("Only BOOLEAN type JsonAttribute contains bool value.");
	}

	return boolValue;
}

void JsonAttribute::addJsonValue(double joId)
{
	if (jat != JsonAttributeType::ARRAY && jat != JsonAttributeType::SINGLE_OBJECT)
	{
		throw runtime_error("Json object can be added only to ARRAY or SINGLEOBJECT JsonAttribute.");
	}

	if (jat == JsonAttributeType::SINGLE_OBJECT && jsonValues.size() > 0)
	{
		throw runtime_error("Only one JsonObject can be set to SINGLEOBJECT JsonAttribute.");
	}

	jsonValues.push_back(joId);
}

double JsonAttribute::getJsonValueAt(int i)
{
	if (jat != JsonAttributeType::ARRAY && jat != JsonAttributeType::SINGLE_OBJECT)
	{
		throw runtime_error("Only ARRAY or SINGLEOBJECT JsonAttribute contains JsonObjects.");
	}

	if (i > (int)jsonValues.size() - 1)
	{
		throw runtime_error("JsonObject index within JsonAttribute array out of bounds.");
	}

	return jsonValues.at(i);
}

int JsonAttribute::getJsonObjectCount()
{
	if (jat != JsonAttributeType::ARRAY && jat != JsonAttributeType::SINGLE_OBJECT)
	{
		throw runtime_error("Only ARRAY or SINGLEOBJECT JsonAttribute contains JsonObjects.");
	}

	return jsonValues.size();
}

JsonAttribute JsonAttribute::createBoolAttribute(string boolValue, string name)
{
	JsonAttribute ja(BOOLEAN, name);
	ja.setBoolValue(boolValue);
	return ja;
}

JsonAttribute JsonAttribute::createNumAttribute(string numValue, string name)
{
	JsonAttribute ja(NUMBER, name);
	ja.setNumValue(numValue);
	return ja;
}
