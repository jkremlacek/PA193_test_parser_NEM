#include "../../h/model/Block.h"

Block::Block()
{
}

Block::~Block()
{
}

bool Block::setVersion(double version)
{
	return false;
}

bool Block::setTimestamp(double timestamp)
{
	return false;
}

bool Block::setHarversterKey(Key key)
{
	return false;
}

bool Block::setSignature(Signature signature)
{
	return false;
}

bool Block::setPrevBlockHash(Hash hash)
{
	return false;
}

bool Block::setGenerationHash(Hash hash)
{
	return false;
}

bool Block::setType(double type)
{
	return false;
}

bool Block::setHeight(double height)
{
	return false;
}

bool Block::addTransaction(Transaction transaction)
{
	return false;
}

bool Block::isValid() {
	bool transactionsValidResult = true;

	for each (Transaction t in this->transactions)
	{
		transactionsValidResult = transactionsValidResult && t.isValid();
	}

	return
		//TODO: define which block versions are allowed
		this->version == 1 &&
		//TODO: validate timestamp
		this->harvesterKey.isValid() &&
		this->signature.isValid() &&
		this->prevBlockHash.isValid() &&
		this->generationHash.isValid() &&
		//TODO: define which block height is valid
		transactionsValidResult;
}
