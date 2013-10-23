<?php
/// \file localization_category.inc.php
/// \brief A part of the SimpleLion project - PHP module. A class that represents category grouping localization strings.
/// \author Phitherek_
/// \date 2013
/// \version 0.1
include('localization_string.inc.php');

/// \namespace SimpleLion
/// \brief A global namespace for the SimpleLion project - PHP module.
namespace SimpleLion;

/// \class LocalizationCategory
/// \brief A class that represents category grouping localization strings.
class LocalizationCategory {
	private $name=null;
	private $subentries=null;
	private $subentriesIterator=null;
	private $subentriesEnd=null;
	function __construct($name=null) {
		$this->name = $name;
		$this->subentries = array();
		$this->subentriesIterator = -1;
		$this->subentriesEnd=true;
	}
	function valid() {
		if($this->name != null && $this->name != "") {
			return true;
		} else {
			return false;
		}
	}
	function addLocalizationEntry($entry) {
		if($this->valid()) {
			if($entry->valid()) {
				$arrsize = count($this->subentries);
				$this->subentries[$arrsize-1] = $entry;
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
	function getNextLocalizationEntry() {
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
	function getLocalizationEntryAt($idx) {
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
	function removeLocalizationEntry($idx) {
		if($this->valid()) {
			if($idx > -1 && $idx < count($this->subentries)) {
				for($i=$idx; $i < count($this->subentries)-1; $i++) {
					$this->subentries[$i] = $this->subentries[$i+1];
				}
				array_pop($this->subentries);
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
	function getLocalizationEntryByName($name) {
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
	function removeLocalizationEntryByName($name) {
		if($this->valid()) {
			for($i=0;$i < count($this->subentries);$i++) {
				if($this->subentries[$i]->name() == $name) {
					$this->deleteLocalizationEntry($i);
					return true;
				}
			}
			return false;
		} else {
			return false;
		}
	}
	function name() {
		if($this->valid()) {
			return $this->name;
		} else {
			return null;
		}
	}
	function resetLocalizationEntryIterator() {
		$this->subentriesIterator = -1;
		if(count($this->subentries) > 0) {
			$this->subentriesEnd = false;
		} else {
			$this->subentriesEnd = true;
		}
	}
	function localizationEntriesAtEnd() {
		return $this->subentriesEnd;
	}
	function setName($name) {
		$this->name = $name;
	}
	function toSLLF() {
		if($this->valid()) {
			$ret = "";
			$ret .= "{";
			$ret .= $this->name;
			$ret .= "}\n";
			for($i=0; $i < count($this->subentries); $i++) {
				$ret .= $this->subentries[$i]->toSLLF();
			}
			$ret .= "{end}\n";
		} else {
			return null;
		}
	}
}
?>
