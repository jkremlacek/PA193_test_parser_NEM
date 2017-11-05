#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/cpp/serialization/JsonAttribute.cpp"
#include "../src/cpp/model/Block.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(JsonAttributeUnitTest) {
	public:

		TEST_METHOD(getSetName_Test) {
			Assert::IsTrue("test" == JsonAttribute(STRING, "test").getName());
		}

		TEST_METHOD(getSetType_Test)	{
			Assert::IsTrue(STRING == JsonAttribute(STRING, "test").getType());
			Assert::IsTrue(ARRAY == JsonAttribute(ARRAY, "test").getType());
			Assert::IsTrue(SINGLE_OBJECT == JsonAttribute(SINGLE_OBJECT, "test").getType());
		}

		TEST_METHOD(getSetTextValue_Array_Test)	{
			JsonAttribute arrayAttr = JsonAttribute(ARRAY, "test");
			Assert::ExpectException<std::exception>([&]
			{
				arrayAttr.setTextValue("testNode");
			});
			Assert::ExpectException<std::exception>([&]
			{
				arrayAttr.getTextValue();
			});
		}

		TEST_METHOD(getSetTextValue_SingleObject_Test) {
			JsonAttribute arrayAttr = JsonAttribute(SINGLE_OBJECT, "test");
			Assert::ExpectException<std::exception>([&]
			{
				arrayAttr.setTextValue("testNode");
			});
			Assert::ExpectException<std::exception>([&]
			{
				arrayAttr.getTextValue();
			});
		}

		TEST_METHOD(getSetData_String_Test) {
			JsonAttribute stringObj = JsonAttribute(STRING, "test");
			stringObj.setTextValue("testLeaf");
			Assert::IsTrue(stringObj.getTextValue() == "testLeaf");
		}

		TEST_METHOD(addJsonValue_Array_Test) {
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");
			Assert::IsTrue(attrObj.getJsonObjectCount() == 0);
			attrObj.addJsonValue(1L);
			Assert::IsTrue(attrObj.getJsonObjectCount() == 1);
		}

		TEST_METHOD(addJsonValue_SingleObject_Test) {
			JsonAttribute attrObj = JsonAttribute(SINGLE_OBJECT, "testAttr");
			Assert::IsTrue(attrObj.getJsonObjectCount() == 0);
			attrObj.addJsonValue(1L);
			Assert::IsTrue(attrObj.getJsonObjectCount() == 1);
		}

		TEST_METHOD(addJsonValue_String_Test) {
			JsonAttribute stringObj = JsonAttribute(STRING, "text");
			Assert::ExpectException<std::exception>([&]
			{
				stringObj.addJsonValue(1L);
			});
		}

		TEST_METHOD(addJsonValues_SingleObject_Test) {
			JsonAttribute attrObj = JsonAttribute(SINGLE_OBJECT, "testAttr");
			Assert::IsTrue(attrObj.getJsonObjectCount() == 0);
			attrObj.addJsonValue(1L);
			Assert::IsTrue(attrObj.getJsonObjectCount() == 1);
			Assert::ExpectException<std::exception>([&]
			{
				attrObj.addJsonValue(1L);
			});
		}		

		TEST_METHOD(getSetNumValue_Test) {
			JsonAttribute attrObj = JsonAttribute(NUMBER, "test");
			attrObj.setNumValue("1000.1001");
			Assert::AreEqual(1000.1001 ,attrObj.getNumValue());
		}

		TEST_METHOD(getSetNumValue_Invalid_Test) {
			JsonAttribute attrObj = JsonAttribute(NUMBER, "test");
			Assert::ExpectException<std::exception>([&]
			{
				attrObj.setNumValue("1000.1001X");
			});
			Assert::ExpectException<std::exception>([&]
			{
				attrObj.setNumValue("1000.10.01");
			});
		}

		TEST_METHOD(getSetBoolValue_Test) {
			JsonAttribute attrObjTrue = JsonAttribute(BOOLEAN, "test1");
			JsonAttribute attrObjFalse = JsonAttribute(BOOLEAN, "test2");
			attrObjTrue.setBoolValue("true");
			attrObjFalse.setBoolValue("false");
			Assert::AreEqual(true, attrObjTrue.getBoolValue());
			Assert::AreEqual(false, attrObjFalse.getBoolValue());
		}

		TEST_METHOD(getSetBoolValue_Invalid_Test) {
			JsonAttribute attrObjTrue = JsonAttribute(BOOLEAN, "test1");
			Assert::ExpectException<std::exception>([&]
			{
				attrObjTrue.setBoolValue("trueX");
			});
		}

		TEST_METHOD(createBoolAttribute_Test) {
			Assert::AreEqual(true, JsonAttribute::createBoolAttribute("true", "boolName").getBoolValue());
		}

		TEST_METHOD(createBoolAttribute_Invalid_Test) {
			Assert::ExpectException<std::exception>([&]
			{
				JsonAttribute::createBoolAttribute("trueX", "boolName").getBoolValue();
			});
		}

		TEST_METHOD(createNumAttribute_Test) {
			Assert::AreEqual(100.1001, JsonAttribute::createNumAttribute("100.1001", "numName").getNumValue());
		}

		TEST_METHOD(createNumAttribute_Invalid_Test) {
			Assert::ExpectException<std::exception>([&]
			{
				Assert::AreEqual(100.1001, JsonAttribute::createNumAttribute("100.1001\"", "numName").getNumValue());
			});
		}
	};
}