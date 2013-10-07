#include "LocalizationString.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main() {
	cout << "Tests for SimpleLion - C++ module (C) 2013 SimpleLion Development Team" << endl;
	cout << "A LocalizationString test v. 0.1" << endl;
	SimpleLion::LocalizationString* str = NULL;
	SimpleLion::LocalizationEntry* entry = NULL;
	int action = 0;
	while(action != 10) {
		cout << endl;
		cout << "1) Create empty LocalizationString" << endl;
		cout << "2) Create LocalizationString with name and value" << endl;
		cout << "3) Display LocalizationString name, type and value" << endl;
		cout << "4) Set LocalizationString name" << endl;
		cout << "5) Set LocalizationString value" << endl;
		cout << "6) Display LocalizationString in SLLF format" << endl;
		cout << "7) Point a LocalizationEntry pointer to LocalizationString" << endl;
		cout << "8) Display LocalizationEntry name and type" << endl;
		cout << "9) Display LocalizationEntry in SLLF format" << endl;
		cout << "10) End this test" << endl;
		cout << "Select action: ";
		cin >> action;
		switch(action) {
		case 1: 
			if(str == NULL) {
				str = new SimpleLion::LocalizationString();
			} else {
				cout << "The string already exists, re-run the test!" << endl;
			}
			break;
		case 2:
			if(str == NULL) {
				cout << "Enter name: ";
				string name;
				cin >> name;
				cout << "Enter value: ";
				string value;
				cin >> value;
				str = new SimpleLion::LocalizationString(name, value);
			} else {
				cout << "The string already exists, re-run the test!" << endl;
			}
			break;
		case 3:
			if(str != NULL) {
				cout << "Name: " << str->name() << endl << "Value: " << str->value() << endl << "Type: " << str->type() << endl;
			} else {
				cout << "The string does not exist. Create one!" << endl;
			}
			break;
		case 4:
			if(str != NULL) {
				cout << "Enter name: ";
				string name;
				cin >> name;
				str->setName(name);
			} else {
				cout << "The string does not exist. Create one!" << endl;
			}
			break;
		case 5:
			if(str != NULL) {
				cout << "Enter value: ";
				string value;
				cin >> value;
				str->setValue(value);
			} else {
				cout << "The string does not exist. Create one!" << endl;
			}
			break;
		case 6:
			if(str != NULL) {
				cout << str->toSLLF();
			} else {
				cout << "The string does not exist. Create one!" << endl;
			}
			break;
		case 7:
			if(str != NULL) {
				if(entry == NULL) {
					entry = str;
				} else {
					cout << "Entry pointer already occupied. Re-run the test!" << endl;
				}
			} else {
				cout << "The string does not exist. Create one!" << endl;
			}
			break;
		case 8:
			if(entry != NULL) {
				cout << "Name: " << entry->name() << endl << "Type: " << entry->type() << endl;
			} else {
				cout << "Entry pointer does not point anywhere!" << endl;
			}
			break;
		case 9:
			if(entry != NULL) {
				cout << entry->toSLLF();
			} else {
				cout << "Entry pointer does not point anywhere!" << endl;
			}
			break;
		case 10:
			if(entry != NULL) {
				entry = NULL;
			}
			if(str != NULL) {
				delete str;
				str = NULL;
			}
			break;
		default: cout << "Unknown action!" << endl; break;
		}
	}
	cout << endl << "END OF TEST" << endl;
	return EXIT_SUCCESS;	
}
