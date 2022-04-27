#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_Insert_and_Find)
		{
			Map<int, int> map;
			map.insert(3, 33);
			map.insert(5, 8);
			map.insert(2, 4);
			map.insert(1, 17);
			map.insert(4, 45);
			map.insert(6, 0);
			map.insert(7, -77);
			Assert::AreEqual(map.find(1),17);
			Assert::AreEqual(map.find(2), 4);
			Assert::AreEqual(map.find(3), 33);
			Assert::AreEqual(map.find(4), 45);
			Assert::AreEqual(map.find(5), 8);
			Assert::AreEqual(map.find(6), 0);
			Assert::AreEqual(map.find(7), -77);
			bool check_invalid_argurent2 = false;
			try
			{
				map.find(10);
			}
			catch (invalid_argument)
			{
				check_invalid_argurent2 = true;
			}
			Assert::IsTrue(check_invalid_argurent2);
		}
		TEST_METHOD(Test_Remove_and_Find1)
		{
			Map<int, int> map;
			map.insert(3, 33);
			map.insert(5, 8);
			map.insert(2, 4);
			map.insert(1, 17);
			map.insert(4, 45);
			map.insert(6, 0);
			map.insert(7, -77);
			map.remove(3);
			Assert::AreEqual(map.find(1), 17);
			Assert::AreEqual(map.find(2), 4);
			Assert::AreEqual(map.find(4), 45);
			Assert::AreEqual(map.find(5), 8);
			Assert::AreEqual(map.find(6), 0);
			Assert::AreEqual(map.find(7), -77);
			bool check_invalid_argurent2 = false;
			try
			{
				map.find(3);
			}
			catch (invalid_argument)
			{
				check_invalid_argurent2 = true;
			}
			Assert::IsTrue(check_invalid_argurent2);

		}
		TEST_METHOD(Test_Remove_and_Find2)
		{
			Map<int, int> map;
			map.insert(3, 33);
			map.insert(5, 8);
			map.insert(2, 4);
			map.insert(1, 17);
			map.insert(4, 45);
			map.insert(6, 0);
			map.insert(7, -77);
			map.remove(5);
			Assert::AreEqual(map.find(1), 17);
			Assert::AreEqual(map.find(2), 4);
			Assert::AreEqual(map.find(3), 33);
			Assert::AreEqual(map.find(4), 45);
			Assert::AreEqual(map.find(6), 0);
			Assert::AreEqual(map.find(7), -77);
			bool check_invalid_argurent = false;
			try
			{
				map.find(5);
			}
			catch (invalid_argument)
			{
				check_invalid_argurent = true;
			}
			Assert::IsTrue(check_invalid_argurent);
		}
		TEST_METHOD(Test_Lists)
		{
			Map<int, int> map;
			map.insert(3, 33);
			map.insert(5, 8);
			map.insert(2, 4);
			map.insert(1, 17);
			map.insert(4, 45);
			map.insert(6, 0);
			map.insert(7, -77);
			List<int> listOfKeys=map.get_keys();
			List<int> listOfValues=map.get_values();
			Assert::AreEqual(listOfKeys.at(0),3);
			Assert::AreEqual(listOfKeys.at(1),2);
			Assert::AreEqual(listOfKeys.at(2),1);
			Assert::AreEqual(listOfKeys.at(3),5);
			Assert::AreEqual(listOfKeys.at(4),4);
			Assert::AreEqual(listOfKeys.at(5),6);
			Assert::AreEqual(listOfKeys.at(6),7);

			Assert::AreEqual(listOfValues.at(0), 33);
			Assert::AreEqual(listOfValues.at(1), 4);
			Assert::AreEqual(listOfValues.at(2), 17);
			Assert::AreEqual(listOfValues.at(3), 8);
			Assert::AreEqual(listOfValues.at(4), 45);
			Assert::AreEqual(listOfValues.at(5), 0);
			Assert::AreEqual(listOfValues.at(6), -77);
		}
		TEST_METHOD(Test_Clear)
		{
			Map<int, int> map;
			map.insert(3, 33);
			map.insert(5, 8);
			map.insert(2, 4);
			map.insert(1, 17);
			map.insert(4, 45);
			map.insert(6, 0);
			map.insert(7, -77);
			Assert::IsFalse(map.get_keys().isEmpty());
			Assert::IsFalse(map.get_values().isEmpty());
			map.clear();
			Assert::IsTrue(map.get_keys().isEmpty());
			Assert::IsTrue(map.get_values().isEmpty());
		}
	};
}
