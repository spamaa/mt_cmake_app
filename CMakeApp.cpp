// CMakeApp.cpp : Defines the entry point for the application.
//

#include "CMakeApp.h"
#include <iostream>
#include <CMakeTopLib.h>
#include <fmt/format.h>

using namespace std;

int main()
{
	// call method from top lib
	::std::cout << "===" << ::std::endl;
	::CMakeTopLib::About();
	::std::cout << ::std::endl;

	// call method from top lib which calls method from underlaying lib
	::std::cout << "===" << ::std::endl;
	CMakeTopLib::AboutStaticLib();
	::std::cout << ::std::endl;

	// call method from library from default registry
	::fmt::print("===\n");
	::fmt::print("This is print from fmt: '{}:{}'\n", __FILE__, __LINE__);
	::fmt::print("\n");

	// call method from top library that triggers ASAN error
	::CMakeTopLib::MakeMemError();

	// ASAN error
	int x[3] = {0, 1, 2};
	::std::cout << "x[3]: '" << x[3] << ::std::endl;

	return 0;
}
