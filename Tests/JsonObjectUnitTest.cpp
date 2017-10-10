#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/cpp/serialization/JsonObject.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(JsonObjectUnitTest) {
	public:

		TEST_METHOD(typeGSTest)	{
			Assert::IsTrue(NODE == JsonObject(NODE).getType());
			Assert::IsTrue(LEAF == JsonObject(LEAF).getType());
		}

		TEST_METHOD(getSetDataNodeTest)	{
			JsonObject nodeObj = JsonObject(NODE);
			Assert::ExpectException<std::exception>([&]
			{
				nodeObj.setData("testNode");
			});
			Assert::ExpectException<std::exception>([&]
			{
				nodeObj.getData();
			});
		}

		TEST_METHOD(getSetDataLeafTest) {
			JsonObject leafObj = JsonObject(LEAF);
			leafObj.setData("testLeaf");
			Assert::IsTrue(leafObj.getData() == "testLeaf");
		}

		TEST_METHOD(addSubObjectTest) {
			JsonObject nodeObj = JsonObject(NODE);
			JsonObject subObj = JsonObject(LEAF);
			Assert::IsTrue(nodeObj.getSubObjectCount() == 0);
			nodeObj.addSubObject("test", subObj);
			Assert::IsTrue(nodeObj.getSubObjectCount() == 1);
			Assert::IsTrue(nodeObj.getSubObjectWithId("test").getType() == subObj.getType());
		}

		TEST_METHOD(addSubObjectLeafTest) {
			JsonObject leafObj = JsonObject(LEAF);
			Assert::ExpectException<std::exception>([&]
			{
				leafObj.addSubObject("test", JsonObject(LEAF));
			});
		}

		TEST_METHOD(addSubObjectEmptyIdTest) {
			JsonObject nodeObj = JsonObject(NODE);
			Assert::IsTrue(nodeObj.getSubObjectCount() == 0);
			nodeObj.addSubObject("", JsonObject(LEAF));
			Assert::IsTrue(nodeObj.getSubObjectCount() == 0);
		}

		TEST_METHOD(getSubObjectWithIdTest) {
			JsonObject nodeObj = JsonObject(NODE);
			JsonObject subObj = JsonObject(LEAF);
			nodeObj.addSubObject("test", subObj);
			Assert::IsTrue(nodeObj.getSubObjectWithId("test").getType() == subObj.getType());
		}

		TEST_METHOD(getSubObjectWithIdMissingTest) {
			JsonObject nodeObj = JsonObject(NODE);
			JsonObject subObj = JsonObject(LEAF);
			nodeObj.addSubObject("test", subObj);
			Assert::ExpectException<std::exception>([&]
			{
				nodeObj.getSubObjectWithId("test1");
			});
		}

		TEST_METHOD(getSubObjectWithIdLeafTest) {
			JsonObject leafObj = JsonObject(LEAF);
			Assert::ExpectException<std::exception>([&]
			{
				leafObj.getSubObjectWithId("test");
			});
		}

		TEST_METHOD(getSubObjectCountTest) {
			JsonObject nodeObj = JsonObject(NODE);
			JsonObject subObj = JsonObject(LEAF);
			Assert::IsTrue(nodeObj.getSubObjectCount() == 0);
			nodeObj.addSubObject("test", subObj);
			Assert::IsTrue(nodeObj.getSubObjectCount() == 1);
			Assert::IsTrue(nodeObj.getSubObjectWithId("test").getType() == subObj.getType());
		}

		TEST_METHOD(getSubObjectCountLeafTest) {
			JsonObject leafObj = JsonObject(LEAF);
			Assert::ExpectException<std::exception>([&]
			{
				leafObj.getSubObjectCount();
			});
		}
		
	};
}