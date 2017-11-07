#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/h/serialization/JsonObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(JsonObjectUnitTest) {
	public:
		TEST_METHOD(getAttributeWithId_Test) {
			JsonObject nodeObj = JsonObject(1L);
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");

			nodeObj.addAttribute(attrObj);
			Assert::IsTrue(nodeObj.getAttributeWithId("testAttr").getType() == JsonAttributeType::ARRAY);
		}

		TEST_METHOD(getAttributeWithId_Missing_Test) {
			JsonObject nodeObj = JsonObject(1L);
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");

			nodeObj.addAttribute(attrObj);
			Assert::ExpectException<std::exception>([&]
			{
				nodeObj.getAttributeWithId("test1");
			});
		}

		TEST_METHOD(getAttributeCount_Test) {
			JsonObject nodeObj = JsonObject(1L);
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");

			Assert::IsTrue(nodeObj.getAttributeCount() == 0);
			nodeObj.addAttribute(attrObj);
			Assert::IsTrue(nodeObj.getAttributeCount() == 1);
		}

		TEST_METHOD(getAttributeCount_MultipleAttr_Test) {
			JsonObject nodeObj = JsonObject(1L);
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");
			JsonAttribute attrObj2 = JsonAttribute(ARRAY, "testAttr2");

			Assert::IsTrue(nodeObj.getAttributeCount() == 0);
			nodeObj.addAttribute(attrObj);
			Assert::IsTrue(nodeObj.getAttributeCount() == 1);
			nodeObj.addAttribute(attrObj2);
			Assert::IsTrue(nodeObj.getAttributeCount() == 2);
		}

		TEST_METHOD(containsAttributeWithId_Test) {
			JsonObject nodeObj = JsonObject(1L);
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");

			Assert::AreEqual(false, nodeObj.containsAttributeWithId("testAttr"));
			nodeObj.addAttribute(attrObj);
			Assert::AreEqual(true, nodeObj.containsAttributeWithId("testAttr"));
		}
	};
}
