#include "../../h/serialization/JsonAttribute.h"

JsonAttribute::JsonAttribute(JsonAttributeType jat, string name): jat(jat), name(name) {
	if (name.length() == 0) throw exception("Json attribute name cannot be empty.");
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
		throw exception("Text value can be set only to STRING type JsonAttribute.");
	}

	textValue = text;
}

const string JsonAttribute::getTextValue()
{
	if (jat != JsonAttributeType::STRING)
	{
		throw exception("Only STRING type JsonAttribute contains text value.");
	}

	return textValue;
}

void JsonAttribute::addJsonValue(double joId)
{
	if (jat != JsonAttributeType::ARRAY && jat != JsonAttributeType::SINGLE_OBJECT)
	{
		throw exception("Json object can be added only to ARRAY or SINGLEOBJECT JsonAttribute.");
	}

	if (jat == JsonAttributeType::SINGLE_OBJECT && jsonValues.size() > 0)
	{
		throw exception("Only one JsonObject can be set to SINGLEOBJECT JsonAttribute.");
	}

	jsonValues.push_back(joId);
}

double JsonAttribute::getJsonValueAt(int i)
{
	if (jat != JsonAttributeType::ARRAY && jat != JsonAttributeType::SINGLE_OBJECT)
	{
		throw exception("Only ARRAY or SINGLEOBJECT JsonAttribute contains JsonObjects.");
	}

	if (i > (int)jsonValues.size() - 1)
	{
		throw exception("JsonObject index within JsonAttribute array out of bounds.");
	}

	return jsonValues.at(i);
}

int JsonAttribute::getJsonObjectCount()
{
	if (jat != JsonAttributeType::ARRAY && jat != JsonAttributeType::SINGLE_OBJECT)
	{
		throw exception("Only ARRAY or SINGLEOBJECT JsonAttribute contains JsonObjects.");
	}

	return jsonValues.size();
}
