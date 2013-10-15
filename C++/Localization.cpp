#include "Localization.h"
#include <fstream>
#include <stack>
using namespace SimpleLion;

Localization::Localization(std::string path) {
	_basepath = new boost::filesystem::path(path.c_str());
	// If directory does not exist, create one. This will certainly help our user.
	if(!boost::filesystem::exists(*_basepath)) {
		if(!boost::filesystem::create_directories(*_basepath)) {
			throw SimpleLion::FilesystemException("Could not create directory!", _basepath->string());
		}	
	}
	_locale = "";
	_file = NULL;
	_fileSize = 0;
	// "Open" the base directory.
	boost::filesystem::directory_iterator begin(*_basepath);
	boost::filesystem::directory_iterator end;
	// Directory should not be empty, because we are loading stuff.
	if(begin == end) {
		throw SimpleLion::FilesystemException("No files present!", _basepath->string());
	}
	// How many SLLF files are there in the directory?
	_localesSize = 0;
	for(boost::filesystem::directory_iterator iter(*_basepath); iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			_localesSize++;
		}
	}
	// Store locale ids (the stem() returns that) into the array.
	if(_localesSize == 0) {
		throw SimpleLion::FilesystemException("No SLLF files present!", _basepath->string());
	}
	_locales = new std::string[_localesSize];
	int i = 0;
	for(boost::filesystem::directory_iterator iter(*_basepath); iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			_locales[i] = (*iter).path().stem().string();
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
			throw SimpleLion::FilesystemException("Could not create directory!", _basepath->string());
		}	
	}
	
	// "Open" the base directory.
	boost::filesystem::directory_iterator begin(*_basepath);
	boost::filesystem::directory_iterator end;
	// Directory should not be empty, because we are loading stuff.
	if(begin == end) {
		throw SimpleLion::FilesystemException("No files present!", _basepath->string());
	}
	// How many SLLF files are there in the directory?
	_localesSize = 0;
	for(boost::filesystem::directory_iterator iter(*_basepath); iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			_localesSize++;
		}
	}
	if(_localesSize == 0) {
		throw SimpleLion::FilesystemException("No SLLF files present!", _basepath->string());
	}
	// Store locale ids (the stem() returns that) into the array.
	_locales = new std::string[_localesSize];
	int i = 0;
	for(boost::filesystem::directory_iterator iter(*_basepath); iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			_locales[i] = (*iter).path().stem().string();
			i++;
		}
	}
	// Check if selected locale file is available
	bool available = false;
	for(int j = 0; j < _localesSize; j++) {
		if(_locales[j] == locale) {
			available = true;
			break;
		}
	}
	if(available) {
		_locale = locale;
	} else {
		throw SimpleLion::FileException("Selected locale is unavailable!");
	}
	
	// Ok, so here we know that the locale exists and also where it is. Time to parse it...
	
	boost::filesystem::path localepath = *_basepath;
	localepath += "/";
	localepath += locale;
	localepath += ".sllf";
	
	// The "for sure" check
	
	if(!boost::filesystem::exists(localepath)) {
		throw SimpleLion::FileException("File does not exist!", localepath.string());
	}
	
	// Parse file to structures
	std::ifstream sllfin(localepath.c_str());
	if(!sllfin) {
		throw SimpleLion::FileException("Could not open file!", localepath.string());
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
			c = sllfin.get();
			if(sllfin) {
				if(c != '\n') {
					line += c;
				}
			} else {
				break;
			}
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
								SimpleLion::LocalizationEntry** newFile = new SimpleLion::LocalizationEntry*[newSize];
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
				value = line;
				if(name == "") {
					std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno <<  " WARNING: Skipping value of invalid/empty string declaration!" << std::endl;
				} else {
					if(value == "") {
						std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno << " WARNING: Skipping empty value of string!" << std::endl;
					} else {
						SimpleLion::LocalizationString* ls = new SimpleLion::LocalizationString(name, value);
						if(cat == NULL) {
							int newSize = _fileSize+1;
							SimpleLion::LocalizationEntry** newFile = new SimpleLion::LocalizationEntry*[newSize];
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
					value = "";
				}
			}
		}
	}
	sllfin.close();
	// We' ve got the file parsed and loaded (or so...). Or the exception has been thrown outside.`
}

Localization::Localization(Localization& cpy) {
	_basepath = new boost::filesystem::path(*(cpy._basepath));
	_locale = cpy._locale;
	_fileSize = cpy._fileSize;
	_localesSize = cpy._localesSize;
	if(cpy._file == NULL) {
		_file = cpy._file;
	} else {
		_file = new SimpleLion::LocalizationEntry*[cpy._fileSize];
		for(int i = 0; i < _fileSize; i++) {
			_file[i] = cpy._file[i];
		}
	}
	if(cpy._locales == NULL) {
		_locales = cpy._locales;
	} else {
		_locales = new std::string[_localesSize];
		for(int i = 0; i < _localesSize; i++) {
			_locales[i] = cpy._locales[i];
		}
	}
}

Localization::~Localization() {
	if(_basepath != NULL) {
		delete _basepath;
	}
	_basepath = NULL;
	_locale = "";
	if(_file != NULL) {
		for(int i = 0; i < _fileSize; i++) {
			delete _file[i];
		}
		delete[] _file;
	}
	_fileSize = 0;
	_file = NULL;
	if(_locales != NULL) {
		delete[] _locales;
	}
	_localesSize = 0;
	_locales = NULL;
}

void Localization::setLocale(std::string locale) {
	// Clear structures if necessary
	if(_file != NULL) {
		for(int i = 0; i < _fileSize; i++) {
			delete _file[i];
		}
		delete[] _file;
		_file = NULL;
		_fileSize = 0;
	}
	// "Open" the base directory.
	boost::filesystem::directory_iterator begin(*_basepath);
	boost::filesystem::directory_iterator end;
	// Directory should not be empty, because we are loading stuff.
	if(begin == end) {
		throw SimpleLion::FilesystemException("No files present!", _basepath->string());
	}
	// How many SLLF files are there in the directory?
	_localesSize = 0;
	for(boost::filesystem::directory_iterator iter(*_basepath); iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			_localesSize++;
		}
	}
	if(_localesSize == 0) {
		throw SimpleLion::FilesystemException("No SLLF files present!", _basepath->string());
	}
	// Store locale ids (the stem() returns that) into the array.
	_locales = new std::string[_localesSize];
	int i = 0;
	for(boost::filesystem::directory_iterator iter(*_basepath); iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			_locales[i] = (*iter).path().stem().string();
			i++;
		}
	}
	// Check if selected locale file is available
	bool available = false;
	for(int j = 0; j < _localesSize; j++) {
		if(_locales[j] == locale) {
			available = true;
			break;
		}
	}
	if(available) {
		_locale = locale;
	} else {
		throw SimpleLion::FileException("Selected locale is unavailable!");
	}
	
	// Ok, so here we know that the locale exists and also where it is. Time to parse it...
	
	boost::filesystem::path localepath = *_basepath;
	localepath += "/";
	localepath += locale;
	localepath += ".sllf";
	
	// The "for sure" check
	
	if(!boost::filesystem::exists(localepath)) {
		throw SimpleLion::FileException("File does not exist!", localepath.string());
	}
	
	// Parse file to structures
	std::ifstream sllfin(localepath.c_str());
	if(!sllfin) {
		throw SimpleLion::FileException("Could not open file!", localepath.string());
	}
	SimpleLion::LocalizationCategory* cat = NULL;
	std::stack<SimpleLion::LocalizationCategory*> catstack;
	std::string name = "", value = "";
	int lineno = 0;
	while(!sllfin.eof()) {
		char c = ' ';
		std::string line;
		lineno++;
		while(c != '\n') {
			c = sllfin.get();
			if(sllfin) {
				if(c != '\n') {
					line += c;
				}
			} else {
				break;
			}
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
								SimpleLion::LocalizationEntry** newFile = new SimpleLion::LocalizationEntry*[newSize];
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
				value = line;
				if(name == "") {
					std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno <<  " WARNING: Skipping value of invalid/empty string declaration!" << std::endl;
				} else {
					if(value == "") {
						std::cout << "SLLF Parser: " << localepath.filename() << ":" << lineno << " WARNING: Skipping empty value of string!" << std::endl;
					} else {
						SimpleLion::LocalizationString* ls = new SimpleLion::LocalizationString(name, value);
						if(cat == NULL) {
							int newSize = _fileSize+1;
							SimpleLion::LocalizationEntry** newFile = new SimpleLion::LocalizationEntry*[newSize];
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
					value = "";
				}
			}
		}
	}
	sllfin.close();
	// We' ve got the file parsed and loaded (or so...). Or the exception has been thrown outside.
}

std::string Localization::query(std::string queryString) {
	SimpleLion::LocalizationCategory* cat = NULL;
	std::string parsed = "";
	if(_file == NULL) {
		return "simplelion:err:no_locale";
	} else {
		for(int i = 0; i < queryString.length(); i++) {
			if(queryString[i] == '.') {
				if(parsed == "") {
					if(cat != NULL) {
						delete cat;
					}
					
					std::string msg = "simplelion:err:invalid_query: " + queryString;
					return msg;
				} else {
					if(cat != NULL) {
						SimpleLion::LocalizationEntry& tmp = cat->getLocalizationEntryByName(parsed);
						if(tmp.type() == "category") {
							cat = dynamic_cast<SimpleLion::LocalizationCategory*>(&tmp);
						} else if(tmp.type() == "entry") {
							std::string msg = "simplelion:err:translation_missing: " + queryString;
							return msg;
						}
					} else {
						bool found = false;
						for(int j = 0; j < _fileSize; j++) {
							SimpleLion::LocalizationEntry *tmp = _file[j];
						if(tmp->type() == "category" && tmp->name() == parsed) {
							cat = dynamic_cast<SimpleLion::LocalizationCategory*>(tmp);
							found = true;
							break;
						}
						}
						if(!found) {
							std::string msg = "simplelion:err:translation_missing: " + queryString;
							return msg;
						}
					}
				}
				parsed = "";
			} else {
				parsed += queryString[i];
			}
		}
		if(parsed == "") {
			std::string msg = "simplelion:err:invalid_query: " + queryString;
			return msg;
		}
		if(cat != NULL) {
			SimpleLion::LocalizationEntry &tmp = cat->getLocalizationEntryByName(parsed);
			if(tmp.type() == "string") {
				return dynamic_cast<SimpleLion::LocalizationString&>(tmp).value();
			} else {
				std::string msg = "simplelion:err:translation_missing: " + queryString;
				return msg;
			}
		} else {
			SimpleLion::LocalizationEntry *tmp;
			for(int i = 0; i < _fileSize; i++) {
				if(_file[i]->name() == parsed && _file[i]->type() == "string") {
					return dynamic_cast<SimpleLion::LocalizationString*>(_file[i])->value();
				}
			}
			std::string msg = "simplelion:err:translation_missing: " + queryString;
			return msg; 
		}                          
	}
}

std::string* Localization::localeList() {
	if(_locales != NULL) {
		delete[] _locales;
		_locales = NULL;
		_localesSize = 0;
	}
	// "Open" the base directory.
	boost::filesystem::directory_iterator begin(*_basepath);
	boost::filesystem::directory_iterator end;
	// Directory should not be empty, because we are loading stuff.
	if(begin == end) {
		throw SimpleLion::FilesystemException("No files present!", _basepath->string());
	}
	// How many SLLF files are there in the directory?
	_localesSize = 0;
	for(boost::filesystem::directory_iterator iter(*_basepath); iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			_localesSize++;
		}
	}
	if(_localesSize == 0) {
		throw SimpleLion::FilesystemException("No SLLF files present!", _basepath->string());
	}
	// Store locale ids (the stem() returns that) into the array.
	_locales = new std::string[_localesSize];
	int i = 0;
	for(boost::filesystem::directory_iterator iter(*_basepath); iter != end; iter++) {
		if((*iter).path().extension().string() == ".sllf") {
			_locales[i] = (*iter).path().stem().string();
			i++;
		}
	}
	return _locales;
}

int Localization::localeListSize() {
	return _localesSize;
}

std::string Localization::toSLLF() {
	if(_file == NULL) {
		return "";
	} else {
		std::string ret = "";
		for(int i = 0; i < _fileSize; i++) {
			ret += _file[i]->toSLLF();
		}
		return ret;
	}
}
