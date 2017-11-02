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

			JsonObject jo = jss.fromString(str);

			Assert::AreEqual(1, jo.getAttributeCount());
			Assert::AreEqual("testName", jo.getAttributeWithId("testName").getName().c_str());
			Assert::AreEqual("testValue", jo.getAttributeWithId("testName").getTextValue().c_str());
		}

		TEST_METHOD(fromString_twoAttributes_Test) {
			string str = "{testName:\"testValue\", testName2:\"testValue2\"}";

			JsonSerializer jss = JsonSerializer();

			JsonObject jo = jss.fromString(str);

			Assert::AreEqual(2, jo.getAttributeCount());
			Assert::AreEqual("testName", jo.getAttributeWithId("testName").getName().c_str());
			Assert::AreEqual("testValue", jo.getAttributeWithId("testName").getTextValue().c_str());
			Assert::AreEqual("testName2", jo.getAttributeWithId("testName2").getName().c_str());
			Assert::AreEqual("testValue2", jo.getAttributeWithId("testName2").getTextValue().c_str());
		}
	};
}