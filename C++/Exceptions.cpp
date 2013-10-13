#include "Exceptions.h"
using namespace SimpleLion;

FilesystemException::FilesystemException(std::string what) {
	_what = what;
	_dirpath = "";
}

FilesystemException::FilesystemException(std::string what, std::string dirpath) {
	_what = what;
	_dirpath = dirpath;
}

FilesystemException::~FilesystemException() throw() {
	_what = "";
	_dirpath = "";
}

const char* FilesystemException::what() const throw() {
	std::string msg = "";
	if(_dirpath != "") {
		msg += _dirpath;
		msg += ": ";
	}
	msg += _what;
	return msg.c_str();
}

FileException::FileException(std::string what) {
	_what = what;
	_filepath = "";
}

FileException::FileException(std::string what, std::string filepath) {
	_what = what;
	_filepath = filepath;
}

FileException::~FileException() throw() {
	_what = "";
	_filepath = "";
}

const char* FileException::what() const throw() {
	std::string msg = "";
	if(_filepath != "") {
		msg += _filepath;
		msg += ": ";
	}
	msg += _what;
	return msg.c_str();
}
