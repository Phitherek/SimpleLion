<?php
/// \file exceptions.inc.php
/// \brief A part of the SimpleLion project - PHP module. Exceptions for the module.
/// \author Phitherek_
/// \date 2013
/// \version 0.1

/// \namespace SimpleLion
/// \brief A global namespace for the SimpleLion project - PHP module.
namespace SimpleLion;

/// \class FileException
/// \brief An exception to be thrown on file error.
class FileException extends Exception {
	private $filepath; ///< A path to the file where error occured.
	private $msg; ///< Error message.
	function __initialize($filepath, $msg) { ///< \brief A constructor from file path and error message.
	///< \param $filepath A path to the file where error occured.
	///< \param $msg Error message.
		$this->filepath = $filepath;
		$this->msg = $msg;
	}
	
	function getMessage() { ///< \brief A function that returns error message.
	///< \return Error message with file path.
		$ret = "";
		$ret .= $filepath;
		$ret .= ": ";
		$ret .= $msg;
		return $ret;
	}
}

/// \class FilesystemException
/// \brief An exception to be thrown on directory error.
class FilesystemException extends Exception {
	private $dirpath; ///< A path to the directory where error occured.
	private $msg; ///< Error message.
	function __initialize($dirpath, $msg) { ///< \brief A constructor from path and error message.
	///< \param $dirpath A path to where error occured.
	///< \param $msg Error message.
		$this->filepath = $dirpath;
		$this->msg = $msg;
	}
	
	function getMessage() { ///< \brief A function that returns error message.
	///< \return Error message with path.
		$ret = "";
		$ret .= $dirpath;
		$ret .= ": ";
		$ret .= $msg;
		return $ret;
	}
}
?>
