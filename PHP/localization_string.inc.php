<?php
/// \file localization_string.inc.php
/// \brief A part of the SimpleLion project - PHP module. A class representing a localized string.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace SimpleLion
/// \brief A global namespace for the SimpleLion project - PHP module.
namespace SimpleLion;

/// \class LocalizationString
/// \brief A class representing a localized string.
class LocalizationString {
	
	private $name=null; ///< Name identifying the string.
	private $value=null; ///< Localized value of the string
	
	function __construct($name=null, $value=null) { ///< \brief A constructor with parameters.
	///< \param $name A name identifying the string, null by default.
	///< \param $value A localized value of the string, null by default.
		$this->name = $name;
		$this->value = $value;
	}
	
	function valid() { ///< \brief A function returning if this LocalizationString object is valid.
	///< \return True if the LocalizationString is valid, which means it has non-empty name and value, false otherwise.
		if($this->name != null && $this->value != null && $this->name != "" && $this->value != "") {
			return true;
		} else {
			return false;
		}
	}
	
	function name() { ///< \brief A function returning name identifying the string.
	///< \return Name identifying the string.
		return $this->name;
	}
	
	function value() { ///< \brief A function returning localized value of the string.
	///< \return Localized value of the string.
		return $this->value;
	}
	
	function setName($name) { ///< \brief A function that sets name identifying the string.
	///< \param $name Name identifying the string.
		$this->name = $name;
	}
	
	function setValue($value) { ///< \brief A function that sets localized value of the string.
	///< \param $value Localized value of the string.
		$this->value = $value;
	}
	
	function toSLLF() { ///< \brief A function that returns a LocalizationString object in the SLLF format.
	///< \return LocalizationString representation in the SLLF format or null if the object is not valid.
		if($this->valid() == true) {
			$ret = "";
			$ret .= "[";
			$ret .= $this->name;
			$ret .= "]\n";
			$ret .= $this->value;
			$ret .= "\n";
			return $ret;
		} else {
			return null;
		}
	}
}
?>
