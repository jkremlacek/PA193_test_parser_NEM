#include "..\..\h\serialization\JsonObject.h"

void JsonObject::addAttribute(JsonAttribute attr) {
	if ((this->attributes.insert(std::pair<string, JsonAttribute>(attr.getName(), attr))).second == false) {
		throw runtime_error(string("Duplicate attribute: " + attr.getName()).c_str());
	}
}

JsonAttribute JsonObject::getAttributeWithId(string id) {
	map<string, JsonAttribute>::iterator it = this->attributes.find(id);

	if (it != this->attributes.end())
	{
		return this->attributes.find(id)->second;
	}

	throw runtime_error(("Object with id: " + id + " was not found.").c_str());
}

int JsonObject::getAttributeCount() {
	return this->attributes.size();
}

bool JsonObject::containsAttributeWithId(string id)
{
	map<string, JsonAttribute>::iterator it = this->attributes.find(id);

	return it != this->attributes.end();
}
