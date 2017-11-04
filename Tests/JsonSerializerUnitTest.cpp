#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/cpp/serialization/JsonSerializer.cpp"

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
			string str = "{testName:\"testValue\"}";

			JsonSerializer jss = JsonSerializer();

			JsonObject* jo = jss.fromString(str).second;

			Assert::AreEqual(1, jo->getAttributeCount());
			Assert::AreEqual("testName", jo->getAttributeWithId("testName").getName().c_str());
			Assert::AreEqual("testValue", jo->getAttributeWithId("testName").getTextValue().c_str());
		}

		TEST_METHOD(fromString_twoAttributes_Test) {
			string str = "{testName:\"testValue\", testName2:\"testValue2\"}";

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
			string str = "{subObjAttr:\"subObjVal\"}, otherAttr:\"otherVal\"";

			JsonSerializer jss = JsonSerializer();

			JsonAttribute ja = jss.getJsonSingleObjAttribute(str, "attrName");
			double newId = ja.getJsonValueAt(0);
			
			Assert::AreEqual(1, jss.getJsonObjectWithId(newId)->getAttributeCount());
			Assert::AreEqual("subObjAttr", jss.getJsonObjectWithId(newId)->getAttributeWithId("subObjAttr").getName().c_str());
		}

		TEST_METHOD(getJsonArrayObjAttribute_Single_Test) {
			string str = "[{subObjAttr:\"subObjVal\"}], otherAttr:\"otherVal\"";

			JsonSerializer jss = JsonSerializer();

			JsonAttribute ja = jss.getJsonArrayObjAttribute(str, "attrName");
			double newId = ja.getJsonValueAt(0);

			Assert::AreEqual(1, jss.getJsonObjectWithId(newId)->getAttributeCount());
			Assert::AreEqual("subObjAttr", jss.getJsonObjectWithId(newId)->getAttributeWithId("subObjAttr").getName().c_str());
		}

		TEST_METHOD(getJsonArrayObjAttribute_Multiple_Test) {
			string str = "[{subObjAttr:\"subObjVal\"} \n, {subObjAttr2:\"subObjVal2\",subObjAttr3:\"subObjVal3\"}], otherAttr:\"otherVal\"";

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
			string str = "{testName:1000.1001}";

			JsonSerializer jss = JsonSerializer();

			JsonObject* jo = jss.fromString(str).second;

			Assert::AreEqual(1, jo->getAttributeCount());
			Assert::AreEqual("testName", jo->getAttributeWithId("testName").getName().c_str());
			Assert::AreEqual(1000.1001, jo->getAttributeWithId("testName").getNumValue());
		}

		TEST_METHOD(fromString_singleAttribute_Bool_Test) {
			string str = "{testName:true}";

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
		}
	};
}