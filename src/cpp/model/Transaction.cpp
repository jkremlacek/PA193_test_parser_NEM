#include "../../h/model/Transaction.h"
#include "../../h/utils/SafeConvertor.h"
#include "../../h/utils/Keccak.h"


/*
Before migration to classes...

int type;
long version;
long time_stamp;
long deadline;
long fee;

typedef struct key_pair {
long long private_key;
string public_key;
} key_pair;

typedef struct address {
string encoded; // base-32 encoded address
string public_key;
bool is_valid;
} address;

typedef struct sender {
key_pair key_pair;
address address;
} sender;

typedef struct signer {
key_pair key_pair;
address address;
} signer;

typedef struct signature {
string r;
string s;
} signature;
*/

Transaction::Transaction() {}

Transaction::~Transaction() {}

bool Transaction::setTimestamp(double timestamp) {
	time_t tmp_t = SafeConvertor::toTime(timestamp);
	if (isTimestampValid(tmp_t)) {
		this->timestamp = tmp_t;
		return true;
	}
	return false;
}
time_t Transaction::getTimestamp() {
	return this->timestamp;
}
bool Transaction::isTimestampValid(time_t timestamp) {
	// TODO: Do not validate against UNIX epoch, use number of seconds since NEM nemesis block creation as "NEM epoch".
	if (timestamp > time(NULL) - NEM_NEMESIS_EPOCH) {
		return false;
	}
	return true;
}

bool Transaction::setAmount(double amount) {
	long long tmp = SafeConvertor::toLong(amount);
	if (isAmountValid(tmp)) {
		this->amount = tmp;
		return true;
	}
	return false;
}
long long Transaction::getAmount() {
	return this->amount;
}
bool Transaction::isAmountValid(long long amount) {
	if (amount < 0) {
		return false;
	}
	return true;
}

bool Transaction::setSignature(Signature signature) {
	if (signature.isValid()) {
		this->signature = signature;
		return true;
	}
	return false;
}
Signature Transaction::getSignature() {
	return this->signature;
}

// TODO: use instead of memcpy due to little/big endian?
/*
void copyIntToByteArray(char* bytes, int start, int value) {
	bytes[start + 0] = (value >> 24) & 0xFF;
	bytes[start + 1] = (value >> 16) & 0xFF;
	bytes[start + 2] = (value >> 8) & 0xFF;
	bytes[start + 3] = value & 0xFF;
}

void copyLongToByteArray(char* bytes, int start, long long value) {
	bytes[start + 0] = (value >> 56) & 0xFF;
	bytes[start + 1] = (value >> 48) & 0xFF;
	bytes[start + 2] = (value >> 40) & 0xFF;
	bytes[start + 3] = (value >> 32) & 0xFF;
	bytes[start + 4] = (value >> 24) & 0xFF;
	bytes[start + 5] = (value >> 16) & 0xFF;
	bytes[start + 6] = (value >> 8) & 0xFF;
	bytes[start + 7] = value & 0xFF;
}
*/

bool Transaction::isSignatureValid(Signature signature) {
	u64 bytes_to_sign_len = 0;
	u64 bytes_to_sign_index = 0;
	//Common part
	//Transaction type: 4 bytes (integer).
	bytes_to_sign_len += 4;
	//Version: 4 bytes (integer).
	bytes_to_sign_len += 4;
	//Timestamp: 4 bytes (integer).
	bytes_to_sign_len += 4;
	//Length of public key byte array (always 32): 4 bytes (integer).
	bytes_to_sign_len += 4;
	//Public key bytes of signer: 32 bytes.
	bytes_to_sign_len += 32;
	//Fee (micro nem): 8 bytes (long).
	bytes_to_sign_len += 8;
	//Deadline: 4 bytes (integer).
	if (this->type == TRANSFER) {
		//Transfer transaction part
		//Length of recipient address(always 40) : 4 bytes(integer).
		bytes_to_sign_len += 4;
		//Recipient address : 40 bytes(using UTF8 encoding).
		bytes_to_sign_len += 40;
		//Amount(micro nem) : 8 bytes(long).
		bytes_to_sign_len += 8;
		//Length of message field : 4 bytes(integer).Note : if the length is 0 then the following 2 fields do not apply.
		bytes_to_sign_len += 4;
		if (this->messagePayload.length() > 0) {
			//Message type : 4 bytes(integer).The following message types are supported.
			bytes_to_sign_len += 4;
			//Length of payload : 4 bytes(integer).
			bytes_to_sign_len += this->messagePayload.length();
			//Payload : UTF8 encoded string.
		}
		//	Note : the following part is optional and only available for version 2 transfer transactions that have an attachment.
		if (version == ((0x68 << 24) + 2) || version == ((0x98 << 24) + 2)) {
			//Number of mosaics : 4 bytes(integer).
			bytes_to_sign_len += 4;
			for each (Mosaic mosaic in this->mosaics) {
				//Length of mosaic structure : 4 bytes(integer).
				bytes_to_sign_len += 4;
				//Length of mosaic id structure : 4 bytes(integer).
				bytes_to_sign_len += 4;
				//Length of namespace id string : 4 bytes(integer).
				bytes_to_sign_len += 4;
				//namespace id string : UTF8 encoded string.
				bytes_to_sign_len += mosaic.getNamespaceId().length();
				//Length of mosaic name string : 4 bytes(integer).
				bytes_to_sign_len += 4;
				//Mosaic name string : UTF8 encoded string.
				bytes_to_sign_len += mosaic.getName().length();
				//Quantity : 8 bytes(long).
				bytes_to_sign_len += 8;
			}
		}
	}
	else if (this->type == TRANSFER_OF_IMPORTANCE) {
		throw runtime_error("Unsupported transaction type TRANSFER_OF_IMPORTANCE");
	}
	else if (this->type == AGGREGATE_MODIFICATION_TRANSACTION) {
		throw runtime_error("Unsupported transaction type AGGREGATE_MODIFICATION_TRANSACTION");
	}
	else if (this->type == MULTISIG_SIGNATURE_TRANSACTION) {
		throw runtime_error("Unsupported transaction type MULTISIG_SIGNATURE_TRANSACTION");
	}
	else if (this->type == MULTISIG_TRANSACTION) {
		throw runtime_error("Unsupported transaction type MULTISIG_TRANSACTION");
	}
	else {
		throw runtime_error("Unknown transaction type.");
	}

	u8* bytes_to_sign = (u8*)malloc((size_t)bytes_to_sign_len);
	if (bytes_to_sign == NULL) {
		throw runtime_error("Couldn't allocate memeory.");
	}

	//Common part
	//Transaction type: 4 bytes (integer).
	memcpy(bytes_to_sign + bytes_to_sign_index, &(this->type), 4);
	bytes_to_sign_index += 4;
	//Version: 4 bytes (integer).
	memcpy(bytes_to_sign + bytes_to_sign_index, &(this->version), 4);
	bytes_to_sign_index += 4;
	//Timestamp: 4 bytes (integer).
	memcpy(bytes_to_sign + bytes_to_sign_index, &(this->timestamp), 4);
	bytes_to_sign_index += 4;
	//Length of public key byte array (always 32): 4 bytes (integer).
	int signer_hash_length = this->signer.getHash().length();
	memcpy(bytes_to_sign + bytes_to_sign_index, &signer_hash_length, 4);
	bytes_to_sign_index += 4;
	//Public key bytes of signer: 32 bytes.
	memcpy(bytes_to_sign + bytes_to_sign_index, &(this->signer.getHash()), 32);
	bytes_to_sign_index += 32;
	//Fee (micro nem): 8 bytes (long).
	memcpy(bytes_to_sign + bytes_to_sign_index, &(this->fee), 8);
	bytes_to_sign_index += 8;
	//Deadline: 4 bytes (integer).
	if (this->type == TRANSFER) {
		//Transfer transaction part
		//Length of recipient address(always 40) : 4 bytes(integer).
		int recipient_hash_length = this->recipient.getHash().length();
		memcpy(bytes_to_sign + bytes_to_sign_index, &recipient_hash_length, 4);
		bytes_to_sign_index += 4;
		//Recipient address : 40 bytes(using UTF8 encoding).
		memcpy(bytes_to_sign + bytes_to_sign_index, &(this->recipient.getHash()), 40);
		bytes_to_sign_index += 40;
		//Amount(micro nem) : 8 bytes(long).
		memcpy(bytes_to_sign + bytes_to_sign_index, &(this->amount), 8);
		bytes_to_sign_index += 8;
		//Length of message field : 4 bytes(integer). Note : if the length is 0 then the following 2 fields do not apply.
		int messaye_payload_length = this->messagePayload.length();
		memcpy(bytes_to_sign + bytes_to_sign_index, &(messaye_payload_length), 4);
		bytes_to_sign_index += 4;
		if (messaye_payload_length > 0) {
			//Message type : 4 bytes(integer).The following message types are supported.
			memcpy(bytes_to_sign + bytes_to_sign_index, &(this->messageType), 4);
			bytes_to_sign_index += 4;
			//Length of payload : 4 bytes(integer).
			// By "Length of message field" they might think payload + int for its size?
			//Payload : UTF8 encoded string.
			memcpy(bytes_to_sign + bytes_to_sign_index, &(this->getMessagePayload()), messaye_payload_length);
			bytes_to_sign_index += messaye_payload_length;
		}
		//	Note : the following part is optional and only available for version 2 transfer transactions that have an attachment.
		if (version == ((0x68 << 24) + 2) || version == ((0x98 << 24) + 2)) {
			//Number of mosaics : 4 bytes(integer).
			int number_of_mosaics = this->mosaics.size();
			memcpy(bytes_to_sign + bytes_to_sign_index, &(number_of_mosaics), 4);
			bytes_to_sign_index += 4;
			for each (Mosaic mosaic in this->mosaics) {
				//Length of mosaic structure : 4 bytes(integer).
				int length_of_mosaic_namespace_id = mosaic.getNamespaceId().length();
				int length_of_mosaic_name = mosaic.getName().length();
				int length_of_mosaic_structure = 4 + length_of_mosaic_namespace_id + 4 + length_of_mosaic_name + 8;
				memcpy(bytes_to_sign + bytes_to_sign_index, &(length_of_mosaic_structure), 4);
				bytes_to_sign_index += 4;
				//Length of mosaic id structure : 4 bytes(integer).
				int length_of_mosaic_id_structure = 4 + length_of_mosaic_namespace_id + 4 + length_of_mosaic_name;
				memcpy(bytes_to_sign + bytes_to_sign_index, &(length_of_mosaic_id_structure), 4);
				bytes_to_sign_index += 4;
				//Length of namespace id string : 4 bytes(integer).
				memcpy(bytes_to_sign + bytes_to_sign_index, &(length_of_mosaic_namespace_id), 4);
				bytes_to_sign_index += 4;
				//namespace id string : UTF8 encoded string.
				memcpy(bytes_to_sign + bytes_to_sign_index, &(mosaic.getNamespaceId()), length_of_mosaic_namespace_id);
				bytes_to_sign_index += length_of_mosaic_namespace_id;
				//Length of mosaic name string : 4 bytes(integer).
				memcpy(bytes_to_sign + bytes_to_sign_index, &(length_of_mosaic_name), 4);
				bytes_to_sign_index += 4;
				//Mosaic name string : UTF8 encoded string.
				memcpy(bytes_to_sign + bytes_to_sign_index, &(mosaic.getName()), length_of_mosaic_name);
				bytes_to_sign_index += length_of_mosaic_name;
				//Quantity : 8 bytes(long).
				long long quantity = mosaic.getQuantity();
				memcpy(bytes_to_sign + bytes_to_sign_index, &(quantity), 8);
			}
		}
	}
	else if (this->type == TRANSFER_OF_IMPORTANCE) {
	}
	else if (this->type == AGGREGATE_MODIFICATION_TRANSACTION) {
	}
	else if (this->type == MULTISIG_SIGNATURE_TRANSACTION) {
	}
	else if (this->type == MULTISIG_TRANSACTION) {
	}
	else {
		throw runtime_error("Unknown transaction type.");
	}

	char* bytes_hex = (char*)malloc((size_t)bytes_to_sign_len * 2 + 1);
	if (bytes_hex == NULL) {
		throw runtime_error("Couldn't allocate memeory.");
	}

	hexencode(bytes_to_sign, (size_t)bytes_to_sign_len, bytes_hex, (size_t)bytes_to_sign_len * 2);
	bytes_hex[(size_t)bytes_to_sign_len * 2] = '\0';

	//cout << "Hex encoded:            " << bytes_hex << endl;

	u8* hash_bytes = (u8*)malloc(32);
	if (hash_bytes == NULL) {
		throw runtime_error("Couldn't allocate memeory.");
	}

	FIPS202_SHA3_256(bytes_to_sign, bytes_to_sign_len, hash_bytes);

	char* hash_bytes_hex = (char*)malloc(2 * 32 + 1);
	if (hash_bytes_hex == NULL) {
		throw runtime_error("Couldn't allocate memeory.");
	}

	hexencode(hash_bytes, 32, hash_bytes_hex, 2 * 32);
	hash_bytes_hex[2 * 32] = '\0';

	//cout << "Hashed and hex encoded: " << hash_bytes_hex << endl;

	//cout << "Original signature:     " << this->signature.getHash() << endl;

	free(bytes_to_sign);
	free(bytes_hex);
	free(hash_bytes);
	free(hash_bytes_hex);

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                                                                                    //
	//  The byte array hex encoded hash is unexpected; TODO: Reverse the bits in ints? Check Docs again.  //
	//                                                                                                    //
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	return true;
}

bool Transaction::setFee(double fee) {
	int tmp = SafeConvertor::toInt(fee);
	// there is always some fee to the transaction
	if (tmp > 0) {
		this->fee = tmp;
		return true;
	}
	return false;
}
int Transaction::getFee() {
	return this->fee;
}
bool Transaction::isFeeValid(int fee) {
	//TODO: Much more to be calculated: https://bob.nem.ninja/docs/#transaction-fees but one would need access the API.
	int expected_fee_at_least = 0;
	if (type == TRANSFER) {
		// Amount not set.
		if (amount == LLONG_MIN) {
			return false;
		}
		long long fee_from_amount = (this->amount / 10000L);
		if (fee_from_amount > 25) {
			expected_fee_at_least += 25;
		}
		else {
			expected_fee_at_least += (int)fee_from_amount; //safe, < 25
		}
		if (isMessagePayloadValid(this->messagePayload) && messagePayload.length() > 0) {
			expected_fee_at_least += (this->messagePayload.length() / 32 + 1);
		}
		// We don't know the maximum quantity and divisibility of a particular mosaic,
		// so we take the floor, which is 1 XEM for a mosaic.
		expected_fee_at_least += this->mosaics.size();
	}
	else if (type == TRANSFER_OF_IMPORTANCE) {
		expected_fee_at_least += 6;
	}
	else if (type == AGGREGATE_MODIFICATION_TRANSACTION) {
		// 10 + 6 * number of modifications + 6 (if a min cosignatory change is involved)
		expected_fee_at_least += 16;
	}
	else if (type == MULTISIG_SIGNATURE_TRANSACTION) {
		expected_fee_at_least += 6;
	}
	else if (type == MULTISIG_TRANSACTION) {
		expected_fee_at_least += 6;
	}
	else {
		return false;
	}

	if (fee >= expected_fee_at_least) {
		return true;
	}

	return false;
}

bool Transaction::setRecipient(Key recipient) {
	if (recipient.isValid()) {
		this->recipient = recipient;
		return true;
	}
	return false;
}
Key Transaction::getRecipient() {
	return this->recipient;
}

bool Transaction::setType(double type) {
	int tmp = SafeConvertor::toInt(type);
	if (isTypeValid(tmp)) {
		this->type = tmp;
		return true;
	}
	return false;
}
int Transaction::getType() {
	return this->type;
}
bool Transaction::isTypeValid(int type) {
	/*
	0x101: Transfer of NEM from sender to recipient.
	0x801: Transfer of importance from sender to remote account.
	0x1001: An aggregate modification transaction, which converts a normal account into a multisig account.
	0x1002: A multisig signature transaction which is used to sign a multisig transaction.
	0x1003: A multisig transaction, which is used for multisig accounts.
	*/
	if (type == TRANSFER || type == TRANSFER_OF_IMPORTANCE || type == AGGREGATE_MODIFICATION_TRANSACTION ||
		type == MULTISIG_SIGNATURE_TRANSACTION || type == MULTISIG_TRANSACTION) {
		return true;
	}
	return false;
}

bool Transaction::setDeadline(double deadline) {
	time_t tmp_t = SafeConvertor::toTime(deadline);
	if (isDeadlineValid(tmp_t)) {
		this->deadline = tmp_t;
		return true;
	}
	return false;
}
time_t Transaction::getDeadline() {
	return this->deadline;
}
bool Transaction::isDeadlineValid(time_t deadline) {
	// The deadline of the transaction. The deadline is given as the number of seconds elapsed since the creation of the nemesis block.
	// If a transaction does not get included in a block before the deadline is reached, it is deleted. 
	// @See: https://bob.nem.ninja/docs/#transaction-objects

	// TODO: Well, the transaction might be overdue, but does it mean the block is invalid?
	/*time_t now = time(NULL) - NEM_NEMESIS_EPOCH;
	if (deadline < now) {
		return false;
	}*/
	// But it could not have been before the NEM epoch...
	if (deadline < 1) {
		return false;
	}
	return true;
}

bool Transaction::setMessagePayload(string messagePayload) {
	if (isMessagePayloadValid(messagePayload)) {
		this->messagePayload = messagePayload;
		return true;
	}
	return false;
}
string Transaction::getMessagePayload() {
	return this->messagePayload;
}
bool Transaction::isMessagePayloadValid(string messagePayload) {
	// Optional field in case the transaction contains a message.The payload is the actual(possibly encrypted) message data.
	// The payload is allowed to have a maximal size of 512 bytes.Transaction validation detects if the limit is exceeded 
	// and returns an error in this case.
	// @See: https://bob.nem.ninja/docs/#transfer-transaction
	if (messagePayload.length() <= 512) {
		return true;
	}
	return false;
}

bool Transaction::setMessageType(double messageType) {
	int tmp = SafeConvertor::toInt(messageType);
	if (isMessageTypeValid(tmp)) {
		this->messageType = tmp;
		return true;
	}
	return false;
}
int Transaction::getMessageType() {
	return this->messageType;
}
bool Transaction::isMessageTypeValid(int messageType) {
	if (messageType == 1 || messageType == 2) {
		return true;
	}
	return false;
}

bool Transaction::setVersion(double version) {
	int tmp = SafeConvertor::toInt(version);
	if (isVersionValid(tmp)) {
		this->version = tmp;
		return true;
	}
	return false;
}
int Transaction::getVersion() {
	return this->version;
}
bool Transaction::isVersionValid(int version) {
	// Network versions:
	//  0x68 << 24 + 1 (1744830465 as 4 byte integer) : the main network version
	//  0x98 << 24 + 1 (-1744830463 as 4 byte integer) : the test network version
	// Transaction version:
	//  0x01
	//  0x02
	if (version == ((0x68 << 24) + 1) || version == ((0x98 << 24) + 1) || version == ((0x68 << 24) + 2) || version == ((0x98 << 24) + 2)) {
		return true;
	}
	return false;
}

bool Transaction::setSigner(Key signer) {
	if (signer.isValid()) {
		this->signer = signer;
		return true;

	}
	return false;
}
Key Transaction::getSigner() {
	return this->signer;
}

bool Transaction::setMosaics(std::list<Mosaic> mosaics) {
	for each (Mosaic mosaic in this->mosaics) {
		if (!mosaic.isValid()) {
			return false;
		}
	}
	this->mosaics = mosaics;
	return true;
}
Key Transaction::getMosaics() {
	return this->signer;
}


bool Transaction::isValid() {
	for each (Mosaic mosaic in this->mosaics) {
		if (!mosaic.isValid()) {
			return false;
		}
	}
	return  isTimestampValid(this->timestamp) &&
		isAmountValid(this->amount) &&
		isSignatureValid(this->signature) &&
		isFeeValid(this->fee) &&
		this->recipient.isValid() &&
		isTypeValid(this->type) &&
		isDeadlineValid(this->deadline) &&
		isMessagePayloadValid(this->messagePayload) &&
		isMessageTypeValid(this->messageType) &&
		isVersionValid(this->version) &&
		this->signer.isValid();
}
