#include "LocalizationCategory.h"
#include "LocalizationString.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main() {
	cout << "Tests for SimpleLion - C++ module (C) 2013 SimpleLion Development Team" << endl;
	cout << "LocalizationCategory test v. 0.1" << endl << endl;
	SimpleLion::LocalizationCategory *category = NULL;
	SimpleLion::LocalizationCategory *category2 = NULL;
	SimpleLion::LocalizationString *str = NULL;
	SimpleLion::LocalizationEntry *entry = NULL;
	int action = 0;
	while(action != 21) {
		cout << "1) Create empty category" << endl;
		cout << "2) Create category with predefined name" << endl;
		cout << "3) Create a LocalizationString" << endl;
		cout << "4) Add a LocalizationString to a category" << endl;
		cout << "5) Iterate through category and display LocalizationEntries" << endl;
		cout << "6) Get LocalizationEntry by index and display it" << endl;
		cout << "7) Get LocalizationEntry by name and display it" << endl;
		cout << "8) Remove LocalizationEntry by index" << endl;
		cout << "9) Remove LocalizationEntry by name" << endl;
		cout << "10) Display category name and type" << endl;
		cout << "11) Set category name" << endl;
		cout << "12) Display category as SLLF" << endl;
		cout << "13) Create category2 with predefined name" << endl;
		cout << "14) Add category to category2" << endl;
		cout << "15) Add LocalizationString to category2" << endl;
		cout << "16) Display category2 as SLLF" << endl;
		cout << "17) Copy category to category2" << endl;
		cout << "18) Copy category2 to LocalizationEntry" << endl;
		cout << "19) Display entry name and type" << endl;
		cout << "20) Display entry as SLLF" << endl;
		cout << "21) Exit test" << endl;
		cout << "Select action: ";
		cin >> action;
		cout << endl;
		string name, value;
		char c;
		switch(action) {
		case 1:
			if(category != NULL) {
				delete category;
			}
			category = new SimpleLion::LocalizationCategory;
			break;
		case 2:
			cout << "Enter name: ";
			cin >> name;
			if(category != NULL) {
				delete category;
			}
			category = new SimpleLion::LocalizationCategory(name);
			break;
		case 3:
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter value: ";
			cin.ignore();
			value = "";
			c = ' ';
			while(c != '\n') {
				c = cin.get();
				if(c != '\n') {
					value += c;
				}
			}
			if(str != NULL) {
				cout << "WARNING: String is not null! This can cause memory leaks if the string has not been added to category, because the test is not deleting it not to accidentaly remove it from category!" << endl;
			}
			str = new SimpleLion::LocalizationString(name, value);
			break;
		case 4:
			if(category != NULL) {
				if(str == NULL) {
					cout << "NOT adding null string to category!" << endl;
				} else {
					category->addLocalizationEntry(*str);
				}
			} else {
				cout << "Create a category first!" << endl;
			}
			break;
		case 5:
			if(category == NULL) {
				cout << "NOT iterating through null!" << endl;
			} else {
				category->resetLocalizationEntryIterator();
				while(!category->localizationEntriesAtEnd()) {
					SimpleLion::LocalizationEntry& le = category->getNextLocalizationEntry();
					if(le.type() != "entry") {
						cout << "Name: " << le.name() << endl << "Type: " << le.type() << endl;
					}
				}
			}
			break;
		case 6:
			if(category == NULL) {
				cout << "NOT searching in null!" << endl;
			} else {
				cout << "Enter index: ";
				int idx;
				cin >> idx;
				SimpleLion::LocalizationEntry& le = category->getLocalizationEntryAt(idx);
				if(le.type() != "entry") {
					cout << "Name: " << le.name() << endl << "Type: " << le.type() << endl;
				} else {
					cout << "There is no entry at this index!" << endl;
				}
			}
			break;
		case 7:
			if(category == NULL) {
				cout << "NOT searching in null!" << endl;
			} else {
				cout << "Enter name: ";
				cin >> name;
				SimpleLion::LocalizationEntry& le = category->getLocalizationEntryByName(name);
				if(le.type() != "entry") {
					cout << "Name: " << le.name() << endl << "Type: " << le.type() << endl;
				} else {
					cout << "There is no entry of this name!" << endl;
				}
			}
			break;
		case 8:
			if(category == NULL) {
				cout << "NOT deleting from null!" << endl;
			} else {
				cout << "Enter index: ";
				int idx;
				cin >> idx;
				category->removeLocalizationEntry(idx);
			}
			break;
		case 9:
			if(category == NULL) {
				cout << "NOT deleting from null!" << endl;
			} else {
				cout << "Enter name: ";
				cin >> name;
				category->removeLocalizationEntryByName(name);
			}
			break;
		case 10:
			if(category == NULL) {
				cout << "NOT displaying null!" << endl;
			} else {
				cout << "Name: " << category->name() << endl << "Type: " << category->type() << endl;
			}
			break;
		case 11:
			if(category == NULL) {
				cout << "NOT setting name of null!" << endl;
			} else {
				cout << "Enter name: ";
				cin >> name;
				category->setName(name);
			}
			break;
		case 12:
			if(category == NULL) {
				cout << "NOT SLLF-ing null!" << endl;
			} else {
				cout << category->toSLLF();
			}
			break;
		case 13:
			cout << "Enter name: ";
			cin >> name;
			if(category2 != NULL) {
				delete category2;
			}
			category2 = new SimpleLion::LocalizationCategory(name);
			break;
		case 14:
			if(category2 == NULL) {
				cout << "NOT adding anything to null!" << endl;
			} else {
				if(category == NULL) {
					cout << "NOT adding null to category2!" << endl;
				} else {
					category2->addLocalizationEntry(*category);
				}
			}
			break;
		case 15:
			if(category2 == NULL) {
				cout << "NOT adding anything to null!" << endl;
			} else {
				if(str == NULL) {
					cout << "NOT adding null to category2!" << endl;
				} else {
					category2->addLocalizationEntry(*str);
				}
			}
			break;
		case 16:
			if(category2 == NULL) {
				cout << "NOT SLLF-ing null!" << endl;
			} else {
				cout << category2->toSLLF();
			}
			break;
		case 17:
			if(category == NULL) {
				cout << "NOT copying null to category2" << endl;
			} else {
				if(category2 != NULL) {
					delete category2;
				}
				category2 = category;
			}
			break;
		case 18:
			if(category2 == NULL) {
				cout << "NOT copying null to entry!" << endl;
			} else {
				if(entry != NULL) {
					delete entry;
				}
				entry = category2;
			}
			break;
		case 19:
			if(entry == NULL) {
				cout << "NOT displaying null!" << endl;
			} else {
				cout << "Name: " << entry->name() << endl << "Type: " << entry->type() << endl;
			}
			break;
		case 20:
			if(entry == NULL) {
				cout << "NOT SLLF-ing null!" << endl;
			} else {
				cout << entry->toSLLF();
			}
			break;
		case 21:
			if(entry != NULL) {
				entry = NULL;
			}
			if(str != NULL) {
				str = NULL;
			}
			if(category2 != NULL) {
				delete category2;
				category2 = NULL;
				category = NULL;
			} else {
				if(category != NULL) {
					delete category;
					category = NULL;
				}
			}
			break;
		default: cout << "Unknown action: " << action << "!" << endl; break;
		}
	}
	cout << "END OF TEST" << endl;
	return EXIT_SUCCESS;
}
