#ifndef _LOCALIZATIONENTRY_H
#define _LOCALIZATIONENTRY_H
#include <string>
/// \file LocalizationEntry.h
/// \brief A part of SimpleLion project - C++ module. Class that represents an entry in localization file.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace SimpleLion
/// \brief A global namespace for SimpleLion project - C++ module.
namespace SimpleLion {

/// \class LocalizationEntry
/// \brief A class that represents an entry in localization file.
class LocalizationEntry {
public:
	virtual std::string type(); ///< \brief A virtual method that returns type of the entry.
	///< \return Type of the entry as string, either entry, category or string.
	virtual std::string name(); ///< \brief A virtual method that returns name of the entry.
	///< \return Name of the entry as string.
};
}
#endif
