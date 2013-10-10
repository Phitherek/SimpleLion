#include "Localization.h"
#include <fstream>
#include <stack>
using namespace SimpleLion;

Localization::Localization(std::string path) {
	_basepath = new boost::filesystem::path(path.c_str());
	// If directory does not exist, create one. This will certainly help our user.
	if(!boost::filesystem::exists(*_basepath)) {
		if(!boost::filesystem::create_directories(*_basepath)) {
			// Filesystem exception
		}	
	}
	_locale = "";
	_file = NULL;
	_fileSize = 0;
	// "Open" the base directory.
	boost::filesystem::directory_iterator begin(*_basepath);
	boost::filesystem::directory_iterator end;
	// Directory should not be empty, because we are loading stuff.
	if(iter == end) {
		// Filesystem exception
	}
	// How many SLLF files are there in the directory?
	int locale_count = 0;
	for(boost::filesystem::directory_iterator iter = begin; iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			locale_count++;
		}
	}
	// Store locale ids (the stem() returns that) into the array.
	_locales = new std::string[locale_count];
	int i = 0;
	for(boost::filesystem::directory_iterator iter = begin; iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			available_locales[i] = (*iter).path().stem().string();
			i++;
		}
	}
}

Localization::Localization(std::string path, std::string locale) {
	_basepath = new boost::filesystem::path(path.c_str());
	_file = NULL;
	_fileSize = 0;
	// If directory does not exist, create one. This will certainly help our user.
	if(!boost::filesystem::exists(*_basepath)) {
		if(!boost::filesystem::create_directories(*_basepath)) {
			// Filesystem exception
		}	
	}
	
	// "Open" the base directory.
	boost::filesystem::directory_iterator begin(*_basepath);
	boost::filesystem::directory_iterator end;
	// Directory should not be empty, because we are loading stuff.
	if(iter == end) {
		// Filesystem exception
	}
	// How many SLLF files are there in the directory?
	int locale_count = 0;
	for(boost::filesystem::directory_iterator iter = begin; iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			locale_count++;
		}
	}
	// Store locale ids (the stem() returns that) into the array.
	_locales = new std::string[locale_count];
	int i = 0;
	for(boost::filesystem::directory_iterator iter = begin; iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			available_locales[i] = (*iter).path().stem().string();
			i++;
		}
	}
	// Check if selected locale file is available
	bool available = false;
	for(int j = 0; j < locale_count; j++) {
		if(available_locales[j] == locale) {
			available = true;
			break;
		}
	}
	if(available) {
		_locale = locale;
	} else {
		// File exception
	}
	
	// Ok, so here we know that the locale exists and also where it is. Time to parse it...
	
	boost::filesystem::path localepath = *_basepath;
	localepath += "/";
	localepath += locale;
	localepath += ".sllf";
	
	// The "for sure" check
	
	if(!boost::filesystem::exists(localepath)) {
		// File exception
	}
	
	// Parse file to structures
	ifstream sllfin(localepath.c_str());
	if(!sllfin) {
		// File exception
	}
	SimpleLion::LocalizationCategory* cat = NULL;
	std::stack<SimpleLion::LocalizationCategory*> catstack;
	std::string name = "", value = "";
	int lineno = 0;
	while(!sllfin.eof()) {
		char c;
		std::string line;
		lineno++;
		while(c != '\n') {
			line += c;
		}
		if(sllfin) {
			if(line[0] == '[') {
				std::string parsed = "";
				bool correct = true;
				for(int i = 1; line[i] != ']'; i++) {
					if(i == line.length()) {
						parsed = "";
						correct = false;
						break;
					} else {
						parsed += line[i];
					}
				}
				if(name != "") {
					std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno << " WARNING: Not adding previous string because found the beginning of another string declaration!" << std::endl;
				}
				if(parsed == "" || !correct) {
					std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno << " WARNING: Skipping invalid/empty string declaration!" << std::endl;
				}
				name = parsed;
			} else if(line[0] == '{') {
				std::string parsed = "";
				bool correct = true;
				for(int i = 1; line[i] != '}'; i++) {
					if(i == line.length()) {
						parsed = "";
						correct = false;
						break;
					} else {
						parsed += line[i];
					}
				}
				if(parsed == "" || !correct) {
					std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno << " WARNING: Skipping invalid/empty category declaration!" << std::endl;
				} else {
					if(parsed == "end") {
						if(cat == NULL) {
							std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno << " WARNING: Encountered end-of-category not matching to a category! Skipping..." << std::endl;
						} else {
							if(!catstack.empty()) {
								SimpleLion::LocalizationCategory* tmpcat = catstack.top();
								catstack.pop();
								tmpcat->addLocalizationEntry(*cat);
								cat = tmpcat;
								tmpcat = NULL;
							} else {
								int newSize = _fileSize+1;
								SimpleLion::LocalizationEntry** newFile = new SimpleLion::LocalizationEntry[newSize];
								if(_file != NULL) {
									for(int i = 0; i < _fileSize; i++) {
										newFile[i] = _file[i];
									}
									delete[] _file;
								}
								newFile[newSize-1] = cat;
								_fileSize = newSize;
								_file = newFile;
								cat = NULL;
							}
						}
					} else {
						if(cat == NULL) {
							cat = new SimpleLion::LocalizationCategory(parsed);
						} else {
							catstack.push(cat);
							cat = new SimpleLion::LocalizationCategory(parsed);
						}
					}
				}
			} else {
				if(name == "") {
					std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno <<  " WARNING: Skipping value of invalid/empty string declaration!" << std::endl;
				} else {
					if(value == "") {
						std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno << " WARNING: Skipping empty value of string!" << std::endl;
					} else {
						SimpleLion::LocalizationString* ls = new SimpleLion::LocalizationString(name, value);
						if(cat == NULL) {
							int newSize = _fileSize+1;
							SimpleLion::LocalizationEntry** newFile = new SimpleLion::LocalizationEntry[newSize];
							if(_file != NULL) {
								for(int i = 0; i < _fileSize; i++) {
									newFile[i] = _file[i];
								}
								delete[] _file;
							}
							newFile[newSize-1] = ls;
							_fileSize = newSize;
							_file = newFile;
						} else {
							cat->addLocalizationEntry(*ls);
						}
					}
					name = "";
					value = ""
				}
			}
		}
	}
	// We' ve got the file parsed and loaded (or so...)
}
