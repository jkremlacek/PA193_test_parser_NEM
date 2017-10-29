#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/h/serialization/JsonSerializer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(JsonSerializerUnitTest) {
		const string tmpJSONFileName = "testJSONfileTMP.json";

	public:

		TEST_METHOD(loadStringFromIfstreamTest) {
			std::ofstream outfile(tmpJSONFileName);
			outfile << "test";
			outfile.flush();
			outfile.close();

			JsonSerializer jss = JsonSerializer();

			Assert::AreEqual(string("test"), jss.loadStringFromFile(tmpJSONFileName.c_str()));

			remove(tmpJSONFileName.c_str());
		};

		TEST_METHOD(removeWhitespacesFromBothSidesTest) {

			string str = "\t   \n \v test \f \v";

			JsonSerializer jss = JsonSerializer();

			Assert::AreEqual("test", jss.removeWhitespacesFromBothSides(str).c_str());
			Assert::AreEqual("test", str.c_str());
		}
	};
}