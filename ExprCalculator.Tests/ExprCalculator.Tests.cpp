#include "CppUnitTest.h"
#include "..\ExprCalculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ExprCalculatorTests
{
	TEST_CLASS(ExprCalculatorTests)
	{
	public:

		TEST_METHOD(TestBasic)
		{
			auto input = "1 + 1";
			auto rp = toReversePolish(input);
			auto res = evaluate(rp);

			Assert::AreEqual<double>(2, res);
		}

		TEST_METHOD(TestBraces)
		{
			auto input = "(1 + 1) * (2+2)";
			auto rp = toReversePolish(input);
			auto res = evaluate(rp);

			Assert::AreEqual<double>(8, res);
		}

		TEST_METHOD(TestPow)
		{
			auto input = "2 ^ 2";
			auto rp = toReversePolish(input);
			auto res = evaluate(rp);

			Assert::AreEqual<double>(4, res);
		}

		TEST_METHOD(TestDivide)
		{
			auto input = "16 / 2";
			auto rp = toReversePolish(input);
			auto res = evaluate(rp);

			Assert::AreEqual<double>(8, res);
		}

		TEST_METHOD(TestNoClosingBracketError)
		{
			Assert::ExpectException<std::logic_error>([]() {
				auto input = "(2 + 2)*(1+4";
				auto rp = toReversePolish(input);
				});
		}

		TEST_METHOD(TestNoOpeningBracketError)
		{
			Assert::ExpectException<std::logic_error>([]() {
				auto input = "(2 + 2)*1+4)";
				auto rp = toReversePolish(input);
				});
		}

		TEST_METHOD(TestInvalidInput)
		{
			Assert::ExpectException<std::logic_error>([]() {
				auto input = "(2 + 2)*(3 % 4)";
				auto rp = toReversePolish(input);
				});
		}
	};
}
