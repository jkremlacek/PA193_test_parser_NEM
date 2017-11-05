#pragma once

#include <time.h>

#include "Validatable.h"
#include "Signature.h"
#include "Key.h"

class Transaction: public Validatable
{
	time_t timestamp;
	int amount;
	Signature signature = nullptr;
	int fee;
	Key recipient = nullptr;
	int type;
	time_t deadline;
	string messagePayload;
	int messageType;
	int version;
	Key signer = nullptr;
public:
	Transaction();
	~Transaction();

	bool setTimestamp(double timestamp);
	bool setAmount(double amount);
	bool setSignature(Signature signature);
	bool setFee(double fee);
	bool setRecipient(Key recipient);
	bool setType(double type);
	bool setDeadline(double deadline);
	bool setMessagePayload(string messagePayload);
	bool setMessageType(double messageType);
	bool setVersion(double version);
	bool setSigner(Key signer);

	bool isValid() override;
};

