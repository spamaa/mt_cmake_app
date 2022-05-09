// CMakeApp.cpp : Defines the entry point for the application.
//

#include "CMakeApp.h"
#include <iostream>
#include <CMakeTopLib.h>

using namespace std;

int main()
{
	::std::cout << "===" << ::std::endl;
	::CMakeTopLib::About();
	::std::cout << ::std::endl;

	::std::cout << "===" << ::std::endl;
	CMakeTopLib::AboutStaticLib();
	::std::cout << ::std::endl;

	return 0;
}
