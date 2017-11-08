#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/h/serialization/JsonSerializer.h"
#include "../src/h/model/Transaction.h"
#include "../src/h/model/Key.h"
#include "../src/h/model/Signature.h"
#include "../src/h/model/Hash.h"

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(JsonSerializerUnitTest) {
		const string tmpJSONFileName = "testJSONfileTMP.json";

	public:

		TEST_METHOD(loadStringFromIfstream_Test) {
			std::ofstream outfile(tmpJSONFileName);
			outfile << "test";
			outfile.flush();
			outfile.close();

			JsonSerializer jss = JsonSerializer();

			Assert::AreEqual(string("test"), jss.loadStringFromFile(tmpJSONFileName.c_str()));

			remove(tmpJSONFileName.c_str());
		};

		TEST_METHOD(removeWhitespacesFromBothSides_Test) {

			string str = "\t   \n \v test \f \v";

			JsonSerializer jss = JsonSerializer();

			Assert::AreEqual("test", jss.removeWhitespacesFromBothSides(str).c_str());
			Assert::AreEqual("test", str.c_str());
		};

		TEST_METHOD(removeWhitespacesFromBothSides_NoWhitespace_Test) {
			string str = "test";

			JsonSerializer jss = JsonSerializer();

			Assert::AreEqual("test", jss.removeWhitespacesFromBothSides(str).c_str());
			Assert::AreEqual("test", str.c_str());
		}

		TEST_METHOD(getJsonStringAttribute_Test) {
			string str = "\"TestValue\",  otherText";

			JsonSerializer jss = JsonSerializer();

			Assert::AreEqual("TestValue", jss.getJsonStringAttribute(str, "AttributeName").getTextValue().c_str());
		}

		TEST_METHOD(fromString_singleAttribute_Test) {
			string str = "{\"testName\":\"testValue\"}";

			JsonSerializer jss = JsonSerializer();

			JsonObject* jo = jss.fromString(str).second;

			Assert::AreEqual(1, jo->getAttributeCount());
			Assert::AreEqual("testName", jo->getAttributeWithId("testName").getName().c_str());
			Assert::AreEqual("testValue", jo->getAttributeWithId("testName").getTextValue().c_str());
		}

		TEST_METHOD(fromString_twoAttributes_Test) {
			string str = "{\"testName\":\"testValue\", \"testName2\":\"testValue2\"}";

			JsonSerializer jss = JsonSerializer();

			JsonObject* jo = jss.fromString(str).second;

			Assert::AreEqual(2, jo->getAttributeCount());
			Assert::AreEqual("testName", jo->getAttributeWithId("testName").getName().c_str());
			Assert::AreEqual("testValue", jo->getAttributeWithId("testName").getTextValue().c_str());
			Assert::AreEqual("testName2", jo->getAttributeWithId("testName2").getName().c_str());
			Assert::AreEqual("testValue2", jo->getAttributeWithId("testName2").getTextValue().c_str());
		}

		TEST_METHOD(fromString_twoAttributesWithSameName_Test) {
			string str = "{testName:\"testValue\", testName:\"testValue2\"}";

			JsonSerializer jss = JsonSerializer();

			Assert::ExpectException<std::exception>([&]
			{
				JsonObject* jo = jss.fromString(str).second;
			});
		}

		TEST_METHOD(getBracketSubstring_Curly_Test) {
			string str = "{{}{}}{{}}";

			JsonSerializer jss = JsonSerializer();

			Assert::AreEqual("{{}{}}", jss.getBracketSubstring(str, CURLY).c_str());
		}

		TEST_METHOD(getBracketSubstring_Square_Test) {
			string str = "[[][]][[]]";

			JsonSerializer jss = JsonSerializer();

			Assert::AreEqual("[[][]]", jss.getBracketSubstring(str, SQUARE).c_str());
		}

		TEST_METHOD(getBracketSubstring_missingBracket_Test) {
			string str = "{{}";

			JsonSerializer jss = JsonSerializer();

			Assert::ExpectException<std::exception>([&]
			{
				jss.getBracketSubstring(str, CURLY).c_str();
			});
		}

		TEST_METHOD(getJsonSingleObjAttribute_Test) {
			string str = "{\"subObjAttr\":\"subObjVal\"}, \"otherAttr\":\"otherVal\"";

			JsonSerializer jss = JsonSerializer();

			JsonAttribute ja = jss.getJsonSingleObjAttribute(str, "attrName");
			double newId = ja.getJsonValueAt(0);
			
			Assert::AreEqual(1, jss.getJsonObjectWithId(newId)->getAttributeCount());
			Assert::AreEqual("subObjAttr", jss.getJsonObjectWithId(newId)->getAttributeWithId("subObjAttr").getName().c_str());
		}

		TEST_METHOD(getJsonArrayObjAttribute_Single_Test) {
			string str = "[{\"subObjAttr\":\"subObjVal\"}], \"otherAttr\":\"otherVal\"";

			JsonSerializer jss = JsonSerializer();

			JsonAttribute ja = jss.getJsonArrayObjAttribute(str, "attrName");
			double newId = ja.getJsonValueAt(0);

			Assert::AreEqual(1, jss.getJsonObjectWithId(newId)->getAttributeCount());
			Assert::AreEqual("subObjAttr", jss.getJsonObjectWithId(newId)->getAttributeWithId("subObjAttr").getName().c_str());
		}

		TEST_METHOD(getJsonArrayObjAttribute_Multiple_Test) {
			string str = "[{\"subObjAttr\":\"subObjVal\"} \n, {\"subObjAttr2\":\"subObjVal2\",\"subObjAttr3\":\"subObjVal3\"}], \"otherAttr\":\"otherVal\"";

			JsonSerializer jss = JsonSerializer();

			JsonAttribute ja = jss.getJsonArrayObjAttribute(str, "attrName");
			double newId0 = ja.getJsonValueAt(0);
			double newId1 = ja.getJsonValueAt(1);

			Assert::AreEqual(1, jss.getJsonObjectWithId(newId0)->getAttributeCount());
			Assert::AreEqual("subObjAttr", jss.getJsonObjectWithId(newId0)->getAttributeWithId("subObjAttr").getName().c_str());

			Assert::AreEqual(2, jss.getJsonObjectWithId(newId1)->getAttributeCount());
			Assert::AreEqual("subObjAttr2", jss.getJsonObjectWithId(newId1)->getAttributeWithId("subObjAttr2").getName().c_str());
			Assert::AreEqual("subObjAttr3", jss.getJsonObjectWithId(newId1)->getAttributeWithId("subObjAttr3").getName().c_str());
		}

		TEST_METHOD(fromString_singleAttribute_Number_Test) {
			string str = "{\"testName\":1000.1001}";

			JsonSerializer jss = JsonSerializer();

			JsonObject* jo = jss.fromString(str).second;

			Assert::AreEqual(1, jo->getAttributeCount());
			Assert::AreEqual("testName", jo->getAttributeWithId("testName").getName().c_str());
			Assert::AreEqual(1000.1001, jo->getAttributeWithId("testName").getNumValue());
		}

		TEST_METHOD(fromString_singleAttribute_IntNumber_Test) {
			string str = "{\"testName\":257}";

			JsonSerializer jss = JsonSerializer();

			JsonObject* jo = jss.fromString(str).second;

			Assert::AreEqual(1, jo->getAttributeCount());
			Assert::AreEqual("testName", jo->getAttributeWithId("testName").getName().c_str());
			Assert::AreEqual(257, (int)jo->getAttributeWithId("testName").getNumValue());
		}

		TEST_METHOD(fromString_singleAttribute_Bool_Test) {
			string str = "{\"testName\":true}";

			JsonSerializer jss = JsonSerializer();

			JsonObject* jo = jss.fromString(str).second;

			Assert::AreEqual(1, jo->getAttributeCount());
			Assert::AreEqual("testName", jo->getAttributeWithId("testName").getName().c_str());
			Assert::AreEqual(true, jo->getAttributeWithId("testName").getBoolValue());
		}

		TEST_METHOD(fromJSONFile_Test) {
			JsonSerializer jss = JsonSerializer();
			
			JsonObject* root = jss.fromJSONFile("../ExampleData/ValidBlock/block.json");

			Assert::IsNotNull(root);
			Assert::AreEqual(8, root->getAttributeCount());
			Assert::AreEqual(79545139.0, root->getAttributeWithId("timeStamp").getNumValue());
			Assert::AreEqual(
				"d2470a1b145aff0ab6fb6869ce2d44894eaaddbf534424f8b0b2432c4799237510216195423843c50b84600458752e53b83c6310ee2347d681b98c32bbcacd00", 
				root->getAttributeWithId("signature").getTextValue().c_str());

			JsonObject* dataJO = jss.getJsonObjectWithId(root->getAttributeWithId("prevBlockHash").getJsonValueAt(0));

			Assert::AreEqual(
				"4b767ff3b59921c4c7f83a12757178e28d7a986ac9a3ccf64a01a4fc937430ce",
				dataJO->getAttributeWithId("data").getTextValue().c_str()
			);
			Assert::AreEqual(1.0, root->getAttributeWithId("type").getNumValue());

			JsonObject* transactionJO_0 = 
				jss.getJsonObjectWithId(root->getAttributeWithId("transactions").getJsonValueAt(0));
			JsonObject* transactionJO_1 =
				jss.getJsonObjectWithId(root->getAttributeWithId("transactions").getJsonValueAt(1));
			JsonObject* transactionJO_2 =
				jss.getJsonObjectWithId(root->getAttributeWithId("transactions").getJsonValueAt(2));

			checkTransaction(
				transactionJO_0,
				jss,
				79545121,
				35000000,
				"5fea0d4572f91f52cc2474fe6e78332d39c02296a1fe2f589c463165eb538f4a2c67a793f28f70cbe11bc7b1580ba23418bcbdf36fe29d2d9f4802b3e6f87c00",
				6250000,
				"NAWY52S4MBWST5JDXDSA4BDDF5GR2CJZ3IZ2DUX7",
				257,
				79552321,
				"4437313032653437346432326262303161",
				1,
				1744830465,
				"2f69c71a7cd584e5f92ff787fb1d68aab53985c577eff6e9061c15768899433c"
			);

			checkTransaction(
				transactionJO_1,
				jss,
				79545087,
				50010000000,
				"91ee593cd316c7898ab9e04fa5e62919844927774540732f375474645febf3391dc41c3ad504f94b44e762c86baba1dd5b5d2de15097ad391800f0761ffbf001",
				300000,
				"ND2JRPQIWXHKAA26INVGA7SREEUMX5QAI6VU7HNR",
				257,
				79631487,
				"64653735326233646266386634306264396632",
				1,
				1744830465,
				"fdc6620a8626b4505c49dddc32aa8fcfde3d977b452af0e7e146e536a2a9e9c2"
			);

			checkTransaction(
				transactionJO_2,
				jss,
				79545111,
				296000000,
				"21552a9629ed44ea1096a6d7201f940c7b2d9adb12f7481cbc8c18cd144b652aa4c87b889f981924b5774f9096a90fd2e8d9e421e1931f49429cdf43dc1fb50b",
				150000,
				"NB4I2PVIBZEJGKRVHHVIGTN2PK5MY4A5MCYIIWZD",
				257,
				79548711,
				"4e6f64652072657761726473207061796f75743a20726f756e6420323539332d32353936",
				1,
				1744830466,
				"d96366cdd47325e816ff86039a6477ef42772a455023ccddae4a0bd5d27b8d23",
				true,
				0
			);

			Assert::AreEqual(1744830465.0, root->getAttributeWithId("version").getNumValue());
			Assert::AreEqual("be1f88671d9b7444250938a6c9dcdd575692de604e0df9bdb8e6d397fa759c07", root->getAttributeWithId("signer").getTextValue().c_str());
			Assert::AreEqual(1313679.0, root->getAttributeWithId("height").getNumValue());
		}

		void checkTransaction(
			JsonObject* transactionObject, JsonSerializer& jss, double timeStamp, double amount, string signature, double fee, 
			string recipient, double type, double deadline, string message_payload,
			double message_type, double version, string signer, bool mosaics = false, int mosaicsCount = 0
		) 
		{
			Assert::AreEqual(timeStamp, transactionObject->getAttributeWithId("timeStamp").getNumValue());
			Assert::AreEqual(amount, transactionObject->getAttributeWithId("amount").getNumValue());
			Assert::AreEqual(signature, transactionObject->getAttributeWithId("signature").getTextValue());
			Assert::AreEqual(fee, transactionObject->getAttributeWithId("fee").getNumValue());
			Assert::AreEqual(recipient, transactionObject->getAttributeWithId("recipient").getTextValue());

			if (mosaics)
			{
				Assert::AreEqual(mosaicsCount, transactionObject->getAttributeWithId("mosaics").getJsonObjectCount());
			}

			Assert::AreEqual(type, transactionObject->getAttributeWithId("type").getNumValue());
			Assert::AreEqual(deadline, transactionObject->getAttributeWithId("deadline").getNumValue());

			JsonObject* message = jss.getJsonObjectWithId(transactionObject->getAttributeWithId("message").getJsonValueAt(0));

			Assert::AreEqual(message_payload, message->getAttributeWithId("payload").getTextValue());
			Assert::AreEqual(message_type, message->getAttributeWithId("type").getNumValue());

			Assert::AreEqual(version, transactionObject->getAttributeWithId("version").getNumValue());
			Assert::AreEqual(signer, transactionObject->getAttributeWithId("signer").getTextValue());
		}

		TEST_METHOD(loadBlock_Test) {
			JsonSerializer jss = JsonSerializer();

			JsonObject* root = jss.fromJSONFile("../ExampleData/ValidBlock/block.json");

			Block b = jss.loadBlock(root);

			Assert::IsTrue(b.isValid());
		}

		TEST_METHOD(loadBlock_MosaicTA_Test) {
			JsonSerializer jss = JsonSerializer();

			JsonObject* root = jss.fromJSONFile("../ExampleData/ValidBlock/block_with_mosaic_TA.json");

			Block b = jss.loadBlock(root);

			Assert::IsTrue(b.isValid());
		}
	};
}