#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/h/serialization/JsonAttribute.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(JsonAttributeUnitTest) {
	public:

		TEST_METHOD(nameGSTest) {
			Assert::IsTrue("test" == JsonAttribute(STRING, "test").getName());
		}

		TEST_METHOD(typeGSTest)	{
			Assert::IsTrue(STRING == JsonAttribute(STRING, "test").getType());
			Assert::IsTrue(ARRAY == JsonAttribute(ARRAY, "test").getType());
			Assert::IsTrue(SINGLE_OBJECT == JsonAttribute(SINGLE_OBJECT, "test").getType());
		}

		TEST_METHOD(getSetTextValueArrayTest)	{
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

		TEST_METHOD(getSetTextValueSingleObjectTest) {
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

		TEST_METHOD(getSetDataStringTest) {
			JsonAttribute stringObj = JsonAttribute(STRING, "test");
			stringObj.setTextValue("testLeaf");
			Assert::IsTrue(stringObj.getTextValue() == "testLeaf");
		}

		TEST_METHOD(addJsonValueArrayTest) {
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");
			Assert::IsTrue(attrObj.getJsonObjectCount() == 0);
			attrObj.addJsonValue(JsonObject());
			Assert::IsTrue(attrObj.getJsonObjectCount() == 1);
		}

		TEST_METHOD(addJsonValueSingleObjectTest) {
			JsonAttribute attrObj = JsonAttribute(SINGLE_OBJECT, "testAttr");
			Assert::IsTrue(attrObj.getJsonObjectCount() == 0);
			attrObj.addJsonValue(JsonObject());
			Assert::IsTrue(attrObj.getJsonObjectCount() == 1);
		}

		TEST_METHOD(addJsonValueStringTest) {
			JsonAttribute stringObj = JsonAttribute(STRING, "text");
			Assert::ExpectException<std::exception>([&]
			{
				stringObj.addJsonValue(JsonObject());
			});
		}

		TEST_METHOD(addJsonValuesSingleObjectTest) {
			JsonAttribute attrObj = JsonAttribute(SINGLE_OBJECT, "testAttr");
			Assert::IsTrue(attrObj.getJsonObjectCount() == 0);
			attrObj.addJsonValue(JsonObject());
			Assert::IsTrue(attrObj.getJsonObjectCount() == 1);
			Assert::ExpectException<std::exception>([&]
			{
				attrObj.addJsonValue(JsonObject());
			});
		}		
	};
}