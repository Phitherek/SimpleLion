#include "Localization.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main() {
	cout << "Tests for SimpleLion - C++ module (C) 2013 SimpleLion Development Team" << endl;
	cout << "Localization test (main test) v. 0.1" << endl;
	std::string wd = getenv("PWD");
	std::string parsed = "";
	std::string upperwd = "";
	for(int i = 0; i < wd.length(); i++) {
		if(wd[i] == '/') {
			upperwd += parsed;
			upperwd += wd[i];
			parsed = "";
		} else {
			parsed += wd[i];
		}
	}
	wd = upperwd + "locale";
	try {
		SimpleLion::Localization loc(wd);
		cout << "Localization object up and working!" << endl;
		string* locales;
		locales = loc.localeList();
		for(int i = 0; i < loc.localeListSize(); i++) {
			cout << "Loading locale: " << locales[i] << endl;
			loc.setLocale(locales[i]);
			cout << "test: " << loc.query("test") << endl;
			cout << "test2: " << loc.query("test2") << endl;
			cout << "test3: " << loc.query("test3") << endl;
			cout << "test4: " << loc.query("test4") << endl;
			cout << "testcat.test: " << loc.query("testcat.test") << endl;
			cout << "testcat.test2: " << loc.query("testcat.test2") << endl;
			cout << "testcat.test3: " << loc.query("testcat.test3") << endl;
			cout << "testcat.test4: " << loc.query("testcat.test4") << endl;
			cout << "testcat.acat.test: " << loc.query("testcat.acat.test") << endl;
			cout << "testcat.acat.test2: " << loc.query("testcat.acat.test2") << endl;
			cout << "testcat: " << loc.query("testcat") << endl;
			cout << "testcat.acat: " << loc.query("testcat.acat") << endl;
			cout << endl;
		}
	} catch(SimpleLion::FilesystemException &exc) {
		cout << "FilesystemException: " << exc.what() << endl;
		return 3;
	} catch(SimpleLion::FileException &exc) {
		cout << "FileException: " << exc.what() << endl;
		return 2;
	} catch(exception &exc) {
		cout << "Exception: " << exc.what() << endl;
		return EXIT_FAILURE;
	}
	cout << "END OF TEST" << endl;
	return EXIT_SUCCESS;
}
