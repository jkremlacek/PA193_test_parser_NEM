#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\src\h\serialization\JsonObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(JsonObjectUnitTest) {
	public:
		TEST_METHOD(getAttributeWithIdTest) {
			JsonObject nodeObj = JsonObject();
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");

			nodeObj.addAttribute(attrObj);
			Assert::IsTrue(nodeObj.getAttributeWithId("testAttr").getType() == JsonAttributeType::ARRAY);
		}

		TEST_METHOD(getAttributeWithIdMissingTest) {
			JsonObject nodeObj = JsonObject();
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");

			nodeObj.addAttribute(attrObj);
			Assert::ExpectException<std::exception>([&]
			{
				nodeObj.getAttributeWithId("test1");
			});
		}

		TEST_METHOD(getAttributeCountTest) {
			JsonObject nodeObj = JsonObject();
			JsonAttribute attrObj = JsonAttribute(ARRAY, "testAttr");

			Assert::IsTrue(nodeObj.getAttributeCount() == 0);
			nodeObj.addAttribute(attrObj);
			Assert::IsTrue(nodeObj.getAttributeCount() == 1);
		}
	};
}
