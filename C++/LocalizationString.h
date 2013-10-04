#ifndef _LOCALIZATIONSTRING_H
#define _LOCALIZATIONSTRING_H
#include "LocalizationEntry.h"
#include <string>
/// \file LocalizationString.h
/// \brief A part of the SimpleLion project - C++ module. Class that represents a single string in localization file.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace SimpleLion
/// \brief A global namespace for SimpleLion project - C++ module.
namespace SimpleLion {
/// \class LocalizationString
/// \brief A class that represents a single string in localization file. Derives from LocalizationEntry.
class LocalizationString: public LocalizationEntry {
private:
	std::string _name;
	std::string _value;
public:
	LocalizationString(); ///< \brief A default constructor.
	LocalizationString(std::string name, std::string value); ///< \brief A constructor with parameters.
	///< \param name A unified name of the string.
	///< \param value A value of the string in specific localization.
	std::string type(); ///< \brief A virtual method that returns type of the entry.
	///< \return Type of the entry as string, either entry, category or string.
	std::string name(); ///< \brief A virtual method that returns name of the entry.
	///< \return Name of the entry as string.
	std::string value(); ///< \brief A method that returns value of the string in specific localization.
	///< \return Value of the string as std::string.
	void setName(std::string name); ///< \brief A method that sets name of the string.
	///< \param name Name of the string.
	void setValue(std::string value); ///< \brief A method that sets value of the string.
	///< \return Value of the string.
	std::string toSLLF(); ///< \brief A virtual method that converts the entry to SLLF format.
	///< \return The entry in SLLF format.
};
}
#endif
