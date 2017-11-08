#pragma once

#include <string>

#include "Validatable.h"

using namespace std;

/*
"mosaics": [
{
	"mosaicId": {
		"namespaceId": "id0",
		"name": "name0"
	},
"quantity": 10
},
{
	"mosaicId": {
		"namespaceId": "id1",
		"name": "name1"
	},
"quantity": 11
}
]
*/

class Mosaic: public Validatable
{
private:
	// A namespace is the NEM version of a domain. You can rent a namespace for the duration of a year by paying a fee. 
	string namespaceId;
	string name;
	// The mosaic quantity. The quantity is always given in smallest units for the mosaic, i.e. 
	// if it has a divisibility of 3 the quantity is given in millis. 
	// @See: https://bob.nem.ninja/docs/#mosaicDefinition
	long long quantity;

	bool isQuantityValid(long long quantity);
	bool isNamespaceIdValid(string namespaceId);
	bool isNameValid(string name);

public:
	Mosaic();
	~Mosaic();

	bool setNamespaceId(string namespaceId);
	string getNamespaceId();
	bool setName(string name);
	string getName();
	bool setQuantity(double quantity);
	long long getQuantity();

	bool isValid() override;
};

