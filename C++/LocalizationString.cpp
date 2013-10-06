#include "LocalizationString.h"
using namespace SimpleLion;

LocalizationString::LocalizationString() {
	_name = "";
	_value = "";
}

LocalizationString::LocalizationString(std::string name, std::string value) {
	_name = name;
	_value = value;
}

std::string LocalizationString::type() {
	return "string";
}

std::string LocalizationString::name() {
	return _name;
}

std::string LocalizationString:value() {
	return _value;
}

std::string LocalizationString::getName() {
	return _name;
}

std::string LocalizationString::getValue() {
	return _value;
}

std::string LocalizationString::toSLLF() {
	std::string out = "";
	out += "[" + _name + "]\n";
	out += _value + "\n";
	return out;
}
