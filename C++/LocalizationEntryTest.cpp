#include "LocalizationEntry.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
cout << "Tests for SimpleLion - C++ module (C) 2013 SimpleLion Development Team" << endl;
cout << "A generic LocalizationEntry test v. 0.1" << endl << endl;
SimpleLion::LocalizationEntry genentry;
cout << "Generic LocalizationEntry name: " << genentry.name() << endl;
cout << "Generic LocalizationEntry type: " << genentry.type() << endl;
cout << endl << "END OF TEST" << endl;
return EXIT_SUCCESS;
}
