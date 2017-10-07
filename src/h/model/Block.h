#pragma once

#include <time.h>
#include <list>

#include "Validatable.h"
#include "Key.h"
#include "Signature.h"
#include "Hash.h"
#include "Transaction.h"

class Block: public Validatable
{
private:
	int version;
	time_t timestamp;
	Key harvesterKey;
	Signature signature;
	Hash prevBlockHash;
	Hash generationHash;
	int height;
	std::list<Transaction> transactions;

public:
	Block();
	~Block();

	bool setVersion(int version);
	bool setTimestamp(time_t timestamp);
	bool setHarversterKey(Key key);
	bool setPrevBlockHash(Hash hash); 
	bool setGenerationHash(Hash hash);
	bool setHeight(int height);
	bool addTransaction(Transaction transaction);

	bool isValid() override;
};

