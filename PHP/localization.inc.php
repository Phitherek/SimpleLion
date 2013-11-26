<?php
/// \file localization.inc.php
/// \brief A part of the SimpleLion project - PHP module. The main class representing a Localization engine.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace SimpleLion
/// \brief A global namespace for the SimpleLion project - PHP module.
namespace SimpleLion;

include("localization_category.inc.php");
include("exceptions.inc.php");

/// \class Localization
/// \brief A class representing the Localization engine.
class Localization {
	private $basepath=null;
	private $locales=array();
	private $locale=null;
	private $file=array();
	function __construct($path, $locale=null) { ///< \brief A constructor that checks given path for locales, loads locale list and optionally opens and parses the specified locale. Throws FileException and FilesystemException on errors.
	///< \param $path A path to locales.
	///< \param $locale Optional locale to open and parse. Can be null.
		if(is_dir($path)) {
			$this->basepath = $path;
		} else {
			if(!mkdir($path)) {
				throw new FilesystemException($path, "Not a valid directory and cannot be created!");
			}
		}
		$this->locales = array();
		$dir = scandir($this->basepath);
		if($dir == false) {
			throw new FilesystemException($this->basepath, "Cannot open the directory!");
		}
		foreach ($dir as $file) {
			if(is_file($this->basepath."/".$file) && explode(".", $file)[1] == "sllf") {
				array_push($this->locales, basename($file, ".sllf"));
			}
		}
		if(empty($this->locales)) {
			throw new FilesystemException($this->basepath, "No SLLF files present in the directory!");
		}
		if($locale != null) {
			$found=false;
			foreach($this->locales as $arrlocale) {
				if($locale == $arrlocale) {
					$found=true;
					break;
				}
			}
			if(!$found) {
				throw new FileException($this->basepath."/".$locale.".sllf", "No such locale!");
			}
			$this->locale = $locale;
			$this->file = array();
			$filepath = $this->basepath."/".$locale.".sllf";
			$fp = fopen($filepath, "r");
			$name = "";
			$value = "";
			$category = null;
			$categories = array();
			$i = 0;
			do {
				$line = fgets($fp);
				if($line != false) {
					$line = trim($line);
					$i++;
					if($line[0] == '[') {
						if($name != "") {
							print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Not adding previous string because found the beginning of another string declaration!\n";
						}
						$parsed = "";
						if($line[strlen($line)-1] == ']') {
							for($j=1; $j<strlen($line)-1; $j++) {
								$parsed .= $line[$j];
							}
						}
						if($parsed == "") {
							print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Skipping invalid/empty string declaration!\n";
						}
						$name = $parsed;
					} else if($line[0] == '{') {
						$parsed = "";
						if($line[strlen($line)-1] == '}') {
							for($j=1; $j<strlen($line)-1; $j++) {
								$parsed .= $line[$j];
							}
						}
						if($parsed == "") {
							print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Skipping invalid/empty category declaration!\n";
						} else {
							if($parsed == "end") {
								if($category == null) {
									print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Encountered end-of-category not matching to a category! Skipping...\n";
								} else {
									$tmpcat = $category;
									$category = array_pop($categories);
									if($category == null) {
										array_push($this->file, $tmpcat);
									} else {
										$category->addLocalizationEntry($tmpcat);
									}
								}
							} else {
								if($category != null) {
									array_push($categories, $category);
								}
								$category = new LocalizationCategory($parsed);
							}
						}
					} else {
						$value = $line;
						if($name == "") {
							print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Skipping value of invalid/empty string declaration!\n";
						} else {
							if($value == "") {
								print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Skipping empty value of string!\n";
							} else {
								$str = new LocalizationString($name, $value);
								if($category == null) {
									array_push($this->file, $str);
								} else {
									$category->addLocalizationEntry($str);
								}
							}
						}
						$name = "";
						$value = "";
					}
				}
			} while(!feof($fp));
			fclose($fp);
		}
	}
	
	function setLocale($locale) { ///< \brief A method that opens and parsers the specified locale. Throws FileException and FilesystemException on errors.
	///< \param $locale Locale to open and parse.
		$this->locales = array();
		$dir = scandir($this->basepath);
		if($dir == false) {
			throw new FilesystemException($this->basepath, "Cannot open the directory!");
		}
		foreach ($dir as $file) {
			if(is_file($this->basepath."/".$file) && explode(".", $file)[1] == "sllf") {
				array_push($this->locales, basename($file, ".sllf"));
			}
		}
		if(empty($this->locales)) {
			throw new FilesystemException($this->basepath, "No SLLF files present in the directory!");
		}
		if($locale != null) {
			$found=false;
			foreach($this->locales as $arrlocale) {
				if($locale == $arrlocale) {
					$found=true;
					break;
				}
			}
			if(!$found) {
				throw new FileException($this->basepath."/".$locale.".sllf", "No such locale!");
			}
			$this->locale = $locale;
			$this->file = array();
			$filepath = $this->basepath."/".$locale.".sllf";
			$fp = fopen($filepath, "r");
			$name = "";
			$value = "";
			$category = null;
			$categories = array();
			$i = 0;
			do {
				$line = fgets($fp);
				if($line != false) {
					$line = trim($line);
					$i++;
					if($line[0] == '[') {
						if($name != "") {
							print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Not adding previous string because found the beginning of another string declaration!\n";
						}
						$parsed = "";
						if($line[strlen($line)-1] == ']') {
							for($j=1; $j<strlen($line)-1; $j++) {
								$parsed .= $line[$j];
							}
						}
						if($parsed == "") {
							print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Skipping invalid/empty string declaration!\n";
						}
						$name = $parsed;
					} else if($line[0] == '{') {
						$parsed = "";
						if($line[strlen($line)-1] == '}') {
							for($j=1; $j<strlen($line)-1; $j++) {
								$parsed .= $line[$j];
							}
						}
						if($parsed == "") {
							print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Skipping invalid/empty category declaration!\n";
						} else {
							if($parsed == "end") {
								if($category == null) {
									print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Encountered end-of-category not matching to a category! Skipping...\n";
								} else {
									$tmpcat = $category;
									$category = array_pop($categories);
									if($category == null) {
										array_push($this->file, $tmpcat);
									} else {
										$category->addLocalizationEntry($tmpcat);
									}
								}
							} else {
								if($category != null) {
									array_push($categories, $category);
								}
								$category = new LocalizationCategory($parsed);
							}
						}
					} else {
						$value = $line;
						if($name == "") {
							print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Skipping value of invalid/empty string declaration!\n";
						} else {
							if($value == "") {
								print "SLLF Parser: ".basename($filepath).":".$i." WARNING: Skipping empty value of string!\n";
							} else {
								$str = new LocalizationString($name, $value);
								if($category == null) {
									array_push($this->file, $str);
								} else {
									$category->addLocalizationEntry($str);
								}
							}
						}
						$name = "";
						$value = "";
					}
				}
			} while(!feof($fp));
			fclose($fp);
		}
	}
	
	function query($queryString) { ///< \brief A method that returns localized string value according to queryString or error message (to fit in the bad translation' s place).
	///< \param queryString A query string, formatted this way: string_name or category_name.category_name.(...).string_name
	///< \return Localized string value or error as string.
		if($queryString == null) {
			return "simplelion:err:invalid_query: null";
		}
		if($queryString == "") {
			return "simplelion:err:invalid_query: empty";
		}
		$splitQuery = explode(".", $queryString);
		if($this->file == null || count($this->file) == 0) {
			return "simplelion:err:no_locale";
		}
		$cat = null;
		foreach($splitQuery as $curr) {
			if($curr == "") {
				return "simplelion:err:invalid_query: ".$queryString;
			} else {
				if($cat == null) {
					$found = false;
					foreach($this->file as $entry) {
						if($entry->name() == $curr) {
							if($splitQuery[count($splitQuery)-1] == $curr) {
								if($entry instanceof LocalizationString) {
									return $entry->value();
								}
							} else {
								if($entry instanceof LocalizationCategory) {
									$cat = $entry;
									$found = true;
								}
							}	
						}
					}
					if(!$found) {
						return "simplelion:err:translation_missing: ".$queryString;
					}
				} else {
					$entry = $cat->getLocalizationEntryByName($curr);
					if($entry == null) {
						return "simplelion:err:translation_missing: ".$queryString;
					}
					if($splitQuery[count($splitQuery)-1] == $curr) {
						if($entry instanceof LocalizationString) {
							return $entry->value();
						} else {
							return "simplelion:err:translation_missing: ".$queryString;
						}
					} else {
						if($entry instanceof LocalizationCategory) {
							$cat = $entry;
						} else {
							return "simplelion:err:translation_missing: ".$queryString;
						}
					}
				}
			}
		}
	}
	
	function localeList() { ///< \brief A method that refreshes and returns list of currently available locales.
	///< \return Array of currently available locale codes.
		$this->locales = array();
		$dir = scandir($this->basepath);
		if($dir == false) {
			throw new FilesystemException($this->basepath, "Cannot open the directory!");
		}
		foreach ($dir as $file) {
			if(is_file($this->basepath."/".$file) && explode(".", $file)[1] == "sllf") {
				array_push($this->locales, basename($file, ".sllf"));
			}
		}
		return $this->locales;
	}
	
	function toSLLF() { ///< \brief A method that returns the Localization object in SLLF format.
	///< \return Localization object in SLLF format, as string.
		if($this->file == null || count($this->file) == 0) {
			return null;
		} else {
			$out = "";
			foreach($this->file as $entry) {
				$out .= $entry->toSLLF();
			}
			return $out;
		}
	}
}
?>
