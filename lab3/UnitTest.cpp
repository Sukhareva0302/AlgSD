#include "pch.h"
#include "CppUnitTest.h"
#include "..\ConsoleApplication1\BestPrices.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Prices prices;
			prices.townList.push_back("Saint-P", "Moscow", 10, 20);
			prices.townList.push_name_only("Moscow");
			prices.townList.update_destanation("Moscow", "Khabarovsk", 1, 35);
			prices.townList.push_name_only("Khabarovsk");
			prices.townList.update_destanation("Saint-P", "Khabarovsk", 14, -1);
			prices.townList.push_back("Vladivostok", "Khabarovsk", 13, 8);
			prices.townList.update_destanation("Vladivostok", "Saint-P", -1, 20);

			prices.FormMatrix_fromFile();
			Assert::AreEqual(prices.get_price("Vladivostok", "Saint-P"), 68);
			Assert::AreEqual(prices.get_price("Moscow", "Vladivostok"), 9);
			Assert::AreEqual(prices.get_price("Saint-P", "Vladivostok"), 19);
		}
	};
}
