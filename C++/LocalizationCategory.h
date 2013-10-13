#ifndef _LOCALIZATIONCATEGORY_H
#define _LOCALIZATIONCATEGORY_H
#include "LocalizationEntry.h"
#include <string>
/// \file LocalizationCategory.h
/// \brief A part of the SimpleLion project - C++ module. Class that represents a category in localization file.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace SimpleLion
/// \brief A global namespace for SimpleLion project - C++ module.
namespace SimpleLion {

/// \class LocalizationCategory
/// \brief A class that represents a category in localization file. Derives from LocalizationEntry.
class LocalizationCategory: public LocalizationEntry {
private:
	std::string _name;
	LocalizationEntry** _subentries; // Entry can be either a string or another category. For polymorphism pointer array is used.
	int _subentriesSize;
	int _subentriesIterator;
	bool _subentriesEnd;
public:
	LocalizationCategory(); ///< \brief A default constructor.
	LocalizationCategory(std::string name); ///< \brief A constructor with parameter.
	///< \param name Category name.
	LocalizationCategory(LocalizationCategory &cpy); ///< \brief A copy constructor.
	///< \param cpy Object to copy.
	~LocalizationCategory(); ///< \brief A destructor.
	void addLocalizationEntry(LocalizationEntry& le); ///< \brief A method adding localization entry to category.
	///< \param le A reference to LocalizationEntry object, which can be either LocalizationString or LocalizationCategory.
	LocalizationEntry& getNextLocalizationEntry(); ///< \brief A method returning next LocalizationEntry from the array or generic LocalizationEntry on failure.
	///< \return A reference to next LocalizationEntry from the list.
	LocalizationEntry& getLocalizationEntryAt(int idx); ///< \brief A method returning LocalizationEntry from given array index or generic LocalizationEntry on failure.
	///< \param idx LocalizationEntry position in array.
	///< \return A reference to LocalizationEntry at given array index.
	void removeLocalizationEntry(int idx); ///< \brief A method removing a LocalizationEntry from given array index.
	///< \param idx LocalizationEntry position in array.
	LocalizationEntry& getLocalizationEntryByName(std::string name); ///< \brief A method returning LocalizationEntry by name or generic LocalizationEntry on failure.
	///< \param name LocalizationEntry name.
	///< \return A reference to LocalizationEntry of given name.
	void removeLocalizationEntryByName(std::string name); ///< \brief A method removing a LocalizationEntry by name.
	///< \param name LocalizationEntry name.
	std::string type(); ///< \brief A virtual method that returns type of the entry.
	///< \return Type of the entry as string, either entry, category or string.
	std::string name(); ///< \brief A virtual method that returns name of the entry.
	///< \return Name of the entry as string.
	void resetLocalizationEntryIterator(); ///< \brief A method that resets the iterator of LocalizationEntry array.
	bool localizationEntriesAtEnd(); ///< \brief A method that returns if LocalizationEntry array iterator has reached its end.
	///< \return True if LocalizationArray iterator has reached its end, false otherwise.
	void setName(std::string name); ///< \brief A function that sets name of the category.
	///< \param name New name of the category.
	std::string toSLLF(); ///< \brief A virtual method that converts the entry to SLLF format.
	///< \return The entry in SLLF format.
};
}
#endif
