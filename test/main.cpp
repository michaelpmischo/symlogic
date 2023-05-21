#include <Expressions/ExpressionTest.h>
#include <iostream>

int main(int argc, char* atgv[])
{
	__SETMODE__
	Mathematics::Expressions::Tests::ExpressionTest test1;
	test1.run();
	__UNSETMODE__

	std::cout << "Press Enter to Exit..." << std::endl;
	std::cin.get();
}