#pragma once

#include <time.h>
#include <list>

#include "Validatable.h"
#include "Key.h"
#include "Signature.h"
#include "Hash.h"
#include "Transaction.h"
#include "../utils/SafeConvertor.h"

using namespace std;

class Block: public Validatable
{
private:
	int version;
	time_t timestamp;
	Key harvesterKey;
	Signature signature;
	Hash prevBlockHash;
	Hash generationHash;
	int type;
	int height;
	std::list<Transaction> transactions;

public:
	Block();
	~Block();

	bool setVersion(double version);
	bool setTimestamp(double timestamp);
	bool setHarversterKey(Key key);
	bool setSignature(Signature signature);
	bool setPrevBlockHash(Hash hash); 
	bool setGenerationHash(Hash hash);
	bool setType(double type);
	bool setHeight(double height);
	bool addTransaction(Transaction transaction);

	bool isValid() override;
};

