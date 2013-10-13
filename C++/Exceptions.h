#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H
#include <exception>
#include <string>
/// \file Exceptions.h
/// \brief A part of the SimpleLion project - C++ module. Exceptions used by the project.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace SimpleLion
/// \brief A global namespace for SimpleLion project - C++ module.
namespace SimpleLion {

/// \class FilesystemException
/// \brief An exception to be thrown on filesystem problems.
class FilesystemException: public std::exception {
private:
	std::string _what;
	std::string _dirpath;
public:
	FilesystemException(std::string what); ///< \brief A constructor with error message.
	///< \param what Error message.
	FilesystemException(std::string what, std::string dirpath); ///< \brief A constructor with error message and directory.
	///< \param what Error message.
	///< \param dirpath Path to the directory where error occured.
	~FilesystemException() throw(); ///< A destructor, as needed by std::exception.
	const char* what() const throw(); ///< \brief A function returning error message.
	///< \return Error message.
};

/// \class FileException
/// \brief An exception to be thrown on file errors.
class FileException: public std::exception {
private:
	std::string _what;
	std::string _filepath;
public:
	FileException(std::string what); ///< \brief A constructor with error message.
	///< \param what Error message.
	FileException(std::string what, std::string filepath); ///< \brief A constructor with error message and file.
	///< \param what Error message.
	///< \param filepath Path to the file where error occured.
	~FileException() throw(); ///< A destructor, as needed by std::exception.
	const char* what() const throw(); ///< \brief A function returning error message.
	///< \return Error message.
};
}
#endif
