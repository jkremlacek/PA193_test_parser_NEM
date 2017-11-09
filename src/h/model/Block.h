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
	Key signer;
	int type;
	int height;
	std::list<Transaction> transactions;

public:
	Block();
	~Block();

	bool setVersion(double version);
	bool setTimestamp(double timestamp);
	void setHarversterKey(Key key);
	void setSignature(Signature signature);
	void setPrevBlockHash(Hash hash); 
	void setGenerationHash(Hash hash);
	bool setType(double type);
	bool setHeight(double height);
	void addTransaction(Transaction transaction);
	void setSigner(Key key);

	bool isValid() override;
};

