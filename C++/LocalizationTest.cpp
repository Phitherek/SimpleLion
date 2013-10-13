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
		cout << "Localization object up and working. What next?" << endl << endl;
		int action = 0;
		while(action != 5) {
			cout << "1) Load a localization file" << endl;
			cout << "2) Query for a translation" << endl;
			cout << "3) Display locale list" << endl;
			cout << "4) Convert Localization back to SLLF and display" << endl;
			cout << "5) Exit test" << endl;
			cout << "Select action: ";
			cin >> action;
			string locale;
			string squery;
			string* locales;
			switch(action) {
			case 1:
				cout << "Enter locale code (e.g. en, pl etc.): ";
				cin >> locale;
				loc.setLocale(locale);
				cout << "Locale successfully loaded!" << endl;
				break;
			case 2:
				cout << "Enter query string: ";
				cin >> squery;
				cout << endl << "Query returned: " << loc.query(squery) << endl;
				break;
			case 3:
				locales = loc.localeList();
				cout << "Available locales:" << endl;
				for(int i = 0; i < loc.localeListSize(); i++) {
					cout << locales[i] << endl;
				}
				break;
			case 4:
				cout << loc.toSLLF();
				break;
			case 5:
				break;
			}
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
