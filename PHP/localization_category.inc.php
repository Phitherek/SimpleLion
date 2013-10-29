<?php
/// \file localization_category.inc.php
/// \brief A part of the SimpleLion project - PHP module. A class that represents category grouping localization strings.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace SimpleLion
/// \brief A global namespace for the SimpleLion project - PHP module.
namespace SimpleLion;

include('localization_string.inc.php');

/// \class LocalizationCategory
/// \brief A class that represents category grouping localization strings.
class LocalizationCategory {
	private $name=null; ///< Name identifying the category
	private $subentries=null; ///< Strings and subcategories inside the category
	private $subentriesIterator=null; ///< Iterator for subentries array
	private $subentriesEnd=null; ///< Indicator if the subentriesIterator has reached end of the array
	function __construct($name=null) { ///< \brief A constructor from name.
	///< \param $name Name of the category, can be null but then the category will be invalid.
		$this->name = $name;
		$this->subentries = array();
		$this->subentriesIterator = -1;
		$this->subentriesEnd=true;
	}
	function valid() { ///< \brief A function that returns if the category object is valid.
	///< \return True if the category object is valid - its name must be non-empty - and false otherwise.
		if($this->name != null && $this->name != "") {
			return true;
		} else {
			return false;
		}
	}
	function addLocalizationEntry($entry) { ///< \brief A function that adds a string or category into the category object.
	///< \param $entry A string or category to insert into the category object.
	///< \return True if the object was inserted, false otherwise.
		if($this->valid()) {
			if($entry->valid()) {
				$arrsize = count($this->subentries);
				$this->subentries[$arrsize] = $entry;
				if($this->subentriesIterator < count($this->subentries)) {
					$this->subentriesEnd = false;
				} else {
					$this->subentriesEnd = true;
				}
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
	function getNextLocalizationEntry() { ///< \brief A function that returns next string or subcategory from category object.
	///< \return Next string or subcategory from category object or null if reached end of the arrray.
		if($this->valid() && $this->subentriesEnd == false) {
			$this->subentriesIterator++;
			if($this->subentriesIterator < count($this->subentries)) {
				return $this->subentries[$this->subentriesIterator];
			} else {
				$this->subentriesEnd = true;
				return null;
			}
		} else {
			return null;
		}
	}
	function getLocalizationEntryAt($idx) { ///< \brief A function that returns string or subcategory from specific index in the subentries array.
	///< \param $idx Index of the entry.
	///< \return Specified entry or null.
		if($this->valid()) {
			if($idx > -1 && $idx < count($this->subentries)) {
				return $this->subentries[$idx];
			} else {
				return null;
			}
		} else {
			return null;
		}
	}
	function removeLocalizationEntry($idx) { ///< \brief A function that removes a string or subcategory from specific index in the subentries array.
	///< \param $idx Index of the entry.
	///< \return True if the entry was removed, false otherwise.									
		if($this->valid()) {
			if($idx > -1 && $idx < count($this->subentries)) {
				for($i=$idx; $i < count($this->subentries)-1; $i++) {
					$this->subentries[$i] = $this->subentries[$i+1];
				}
				array_pop($this->subentries);
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
	function getLocalizationEntryByName($name) { ///< \brief A function that returns string or subcategory with specific name..
	///< \param $name Name of the entry.
	///< \return Specified entry or null.
		if($this->valid()) {
			foreach($this->subentries as $entry) {
				if($entry->name() == $name) {
					return $entry;
				}
			}
			return null;
		} else {
			return null;
		}
	}
	function removeLocalizationEntryByName($name) { ///< \brief A function that removes string or subcategory with specific name..
	///< \param $name Name of the entry.
	///< \return True if the entry was removed, false otherwise.
		if($this->valid()) {
			for($i=0;$i < count($this->subentries);$i++) {
				if($this->subentries[$i]->name() == $name) {
					$this->removeLocalizationEntry($i);
					return true;
				}
			}
			return false;
		} else {
			return false;
		}
	}
	function name() { ///< \brief A function that returns name of the category.
	///< \return Name of the category or null if the category is not valid.
		if($this->valid()) {
			return $this->name;
		} else {
			return null;
		}
	}
	function resetLocalizationEntryIterator() { ///< A function, that resets iterator of the subentries array.
		$this->subentriesIterator = -1;
		if(count($this->subentries) > 0) {
			$this->subentriesEnd = false;
		} else {
			$this->subentriesEnd = true;
		}
	}
	function localizationEntriesAtEnd() { ///< \brief A function that returns if the iterator of the subentries array has reached its end.
	///< \return True if the iterator of the subentries array has reached its end, false otherwise.
		return $this->subentriesEnd;
	}
	function setName($name) { ///< \brief A function that sets name of the category.
	///< \param $name New name of the category.
		$this->name = $name;
	}
	function toSLLF() { ///< \brief A function that returns a category object in SLLF format.
	///< \return SLLF representation of the object or null if object is not valid.
		if($this->valid()) {
			$ret = "";
			$ret .= "{";
			$ret .= $this->name;
			$ret .= "}\n";
			for($i=0; $i < count($this->subentries); $i++) {
				$ret .= $this->subentries[$i]->toSLLF();
			}
			$ret .= "{end}\n";
			return $ret;
		} else {
			return null;
		}
	}
}
?>
