#include "../../h/model/Block.h"

#include <list>

Block::Block()
{
}


Block::~Block()
{
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
