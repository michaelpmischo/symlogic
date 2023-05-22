#include <Expressions/ExpressionTest.h>
#include <iostream>

int main(int argc, char* atgv[])
{
	__SETMODE__
	Mathematics::Tests::ExpressionTest test1;
	test1.run();
	__UNSETMODE__
}