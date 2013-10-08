#include "LocalizationCategory.h"
using namespace SimpleLion;

LocalizationCategory::LocalizationCategory() {
	_name = "";
	_subentries = NULL;
	_subentriesSize = 0;
	_subentriesIterator = -1;
	_subentriesEnd = true;
}

LocalizationCategory::LocalizationCategory(std::string name) {
	_name = name;
	_subentries = NULL;
	_subentriesSize = 0;
	_subentriesIterator = -1;
	_subentriesEnd = true;
}

LocalizationCategory::LocalizationCategory(LocalizationCategory& cpy) {
	_name = cpy._name;
	if(cpy._subentries != NULL) {
		_subentries = new LocalizationEntry*[cpy._subentriesSize];
		for(int i = 0; i < cpy._subentriesSize; i++) {
			_subentries[i] = cpy._subentries[i];
		}
	} else {
		_subentries = NULL;
	}
	_subentriesSize = cpy._subentriesSize;
	_subentriesIterator = -1;
	if(_subentriesSize > 0) {
		_subentriesEnd = false;
	} else {
		_subentriesEnd = true;
	}
}

LocalizationCategory::~LocalizationCategory() {
	_name = "";
	if(_subentries != NULL) {
		for(int i = 0; i < _subentriesSize; i++) {
			delete _subentries[i];
		}
		delete[] _subentries;
	}
	_subentries = NULL;
	_subentriesSize = 0;
	_subentriesIterator = -1;
	_subentriesEnd = true;
}

void LocalizationCategory::addLocalizationEntry(LocalizationEntry& le) {
	if(_subentries != NULL) {
		int newSize = _subentriesSize + 1;
		LocalizationEntry** newSubentries = new LocalizationEntry*[newSize];
		for(int i = 0; i < _subentriesSize; i++) {
			newSubentries[i] = _subentries[i];
		}
		delete[] _subentries;
		newSubentries[newSize-1] = &le;
		_subentries = newSubentries;
		_subentriesSize = newSize;
		if(_subentriesIterator < _subentriesSize) {
			_subentriesEnd = false;
		} else {
			_subentriesEnd = true;
		}
	} else {
		_subentriesSize++;
		_subentries = new LocalizationEntry*[_subentriesSize];
		_subentries[_subentriesSize-1] = &le;
		if(_subentriesIterator < _subentriesSize) {
			_subentriesEnd = false;
		} else {
			_subentriesEnd = true;
		}
	}
}

LocalizationEntry& LocalizationCategory::getNextLocalizationEntry() {
	_subentriesIterator++;
	if(_subentriesIterator >= _subentriesSize) {
		_subentriesEnd = true;
	} else {
		_subentriesEnd = false;
	}
	if(_subentriesEnd == true) {
		static LocalizationEntry le;
		return le;
	} else {
		return *(_subentries[_subentriesIterator]);
	}
}

LocalizationEntry& LocalizationCategory::getLocalizationEntryAt(int idx) {
	if(idx > -1 && idx < _subentriesSize) {
		return *(_subentries[idx]);
	} else {
		static LocalizationEntry le;
		return le;
	}
}

void LocalizationCategory::removeLocalizationEntry(int idx) {
	if(idx > -1 && idx < _subentriesSize) {
		LocalizationEntry* torem = _subentries[idx];
		int newSize = _subentriesSize-1;
		if(newSize > 0) {
			LocalizationEntry** newSubentries = new LocalizationEntry*[newSize];
			int i;
			for(i = 0; i < idx; i++) {
				newSubentries[i] = _subentries[i];
			}
			i++;
			for(; i < _subentriesSize; i++) {
				newSubentries[i-1] = _subentries[i];
			}
			delete[] _subentries;
			_subentries = newSubentries;
		} else {
			delete[] _subentries;
			_subentries = NULL;
		}
		_subentriesSize = newSize;
		if(_subentriesIterator >= _subentriesSize) {
			_subentriesEnd = true;
		} else {
			_subentriesEnd = false;
		}
		delete torem;
	}
}

LocalizationEntry& LocalizationCategory::getLocalizationEntryByName(std::string name) {
	for(int i = 0; i < _subentriesSize; i++) {
		if(_subentries[i]->name() == name) {
			return *(_subentries[i]);
		}
	}
	static LocalizationEntry le;
	return le;
}

void LocalizationCategory::removeLocalizationEntryByName(std::string name) {
	for(int i = 0; i < _subentriesSize; i++) {
		if(_subentries[i]->name() == name) {
			removeLocalizationEntry(i);
			return;
		}
	}
}

std::string LocalizationCategory::type() {
	return "category";
}

std::string LocalizationCategory::name() {
	return _name;
}

void LocalizationCategory::resetLocalizationEntryIterator() {
	_subentriesIterator = -1;
	if(_subentriesSize > 0) {
		_subentriesEnd = false;
	} else {
		_subentriesEnd = true;
	}
}

bool LocalizationCategory::localizationEntriesAtEnd() {
	return _subentriesEnd;
}

void LocalizationCategory::setName(std::string name) {
	_name = name;
}

std::string LocalizationCategory::toSLLF() {
	std::string out = "";
	out += "{" + _name + "}\n";
	for(int i = 0; i < _subentriesSize; i++) {
		out += _subentries[i]->toSLLF();
	}
	out += "{end}\n";
	return out;
}
