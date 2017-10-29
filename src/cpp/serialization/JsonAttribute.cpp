#include "../../h/serialization/JsonAttribute.h"

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
		throw new exception("Text value can be set only to STRING type JsonAttribute.");
	}

	textValue = text;
}

const string JsonAttribute::getTextValue()
{
	if (jat != JsonAttributeType::STRING)
	{
		throw new exception("Only STRING type JsonAttribute contains text value.");
	}

	return textValue;
}

void JsonAttribute::addJsonValue(JsonObject jo)
{
	if (jat != JsonAttributeType::ARRAY && jat != JsonAttributeType::SINGLE_OBJECT)
	{
		throw new exception("Json object can be added only to ARRAY or SINGLEOBJECT JsonAttribute.");
	}

	if (jat == JsonAttributeType::SINGLE_OBJECT && jsonValues.size() > 0)
	{
		throw new exception("Only one JsonObject can be set to SINGLEOBJECT JsonAttribute.");
	}

	jsonValues.push_back(jo);
}

const JsonObject JsonAttribute::getJsonValueAt(int i)
{
	if (jat != JsonAttributeType::ARRAY && jat != JsonAttributeType::SINGLE_OBJECT)
	{
		throw new exception("Only ARRAY or SINGLEOBJECT JsonAttribute contains JsonObjects.");
	}

	if (i > jsonValues.size() - 1)
	{
		throw new exception("JsonObject index within JsonAttribute array out of bounds.");
	}

	return jsonValues.at(i);
}

int JsonAttribute::getJsonObjectCount()
{
	if (jat != JsonAttributeType::ARRAY && jat != JsonAttributeType::SINGLE_OBJECT)
	{
		throw new exception("Only ARRAY or SINGLEOBJECT JsonAttribute contains JsonObjects.");
	}

	return jsonValues.size();
}
