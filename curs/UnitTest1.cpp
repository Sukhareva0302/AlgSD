#include "pch.h"
#include "CppUnitTest.h"
#include"..\ConsoleApplication2\Algorithm.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string str = "S O 3/S P 3/O Q 3/O P 2/P R 2/Q R 4/Q T 2/R T 3";
			NodeList list = form_List_from_string(str);
			Assert::AreEqual(maxFlow(list, "S", "T"), 5);
		}
		TEST_METHOD(TestMethod2)
		{
			string str = "A B 7/A C 4/B C 4/B E 2/C E 8/C D 4/E D 4/E F 5/D F 12";
			NodeList list = form_List_from_string(str);
			Assert::AreEqual(maxFlow(list, "A", "F"), 10);
		}
		TEST_METHOD(TestMethod3)
		{
			string str = "S B 3/B D 5/D C 6/D T 5/S A 5/A B 4/A C 2/C T 7";
			NodeList list = form_List_from_string(str);
			Assert::AreEqual(maxFlow(list, "S", "T"), 7);
		}

	};
}
