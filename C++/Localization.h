#ifndef _LOCALIZATION_H
#define _LOCALIZATION_H
#include <string>
#include "LocalizationEntry.h"
#include "LocalizationString.h"
#include "LocalizationCategory.h"
#include "boost/filesystem.hpp"
#include "Exceptions.h"
/// \file Localization.h
/// \brief A part of the SimpleLion project - C++ module. A main class representing localization file.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace SimpleLion
/// \brief A global namespace for SimpleLion project - C++ module.
namespace SimpleLion {

/// \class Localization
/// \brief A main class representing localization file.
class Localization {
private:
	boost::filesystem::path* _basepath;
	std::string _locale;
	LocalizationEntry** _file;
	int _fileSize;
	std::string* _locales;
	int _localesSize;
public:
	Localization(std::string path); ///< \brief A constructor from path. Does not parse any localization file.
	///< \param path A base path for localizations (directory with SLLF files).
	Localization(std::string path, std::string locale); ///< \brief A constructor from path and locale. Loads and parses the localization file.
	///< \param path A base path for localizations (directory with SLLF files).
	///< \param locale A locale id to load (e.g. en, pl etc.)
	Localization(Localization& cpy); ///< \brief A copy constructor.
	///< \param cpy Object to copy.
	~Localization(); ///< A destructor.
	void setLocale(std::string locale); ///< \brief A function that sets, loads and parses specified locale.
	///< \param locale Locale to set, load and parse.
	std::string query(std::string queryString); ///< \brief A function that finds a translated string according to specified query string.
	///< \param queryString A query string, either string_name or category.category.....string_name
	///< \return A translated string or error message.
	std::string* localeList(); ///< \brief A function that returns a list of available locales.
	///< \return A list of available locales as array of locale ids.
	int localeListSize(); ///< \brief A function that returns locale list size.
	///< \return Locale list size (not refreshing, to refresh use localeList() first).
	std::string toSLLF(); ///< \brief A function that returns Localization in SLLF format.
	///< \return Localization in SLLF format.
};
}

#endif
