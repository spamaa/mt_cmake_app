// CMakeApp.cpp : Defines the entry point for the application.
//

#include "CMakeApp.h"
#include <iostream>
#include <CMakeStaticLib.h>

using namespace std;

int main()
{
	cout << "Message from beicode" << endl;
	CMakeStaticLib::About();

	return 0;
}
