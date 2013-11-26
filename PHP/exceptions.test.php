<?php
include("exceptions.inc.php");
print "SimpleLion PHP module tests - (C) 2013 SimpleLion Development Team\n";
print "Exceptions test v.0.1\n";
print "FileException...\n";
try {
	throw new SimpleLion\FileException("/some/file.ext", "Test message!");
} catch(SimpleLion\FileException $e) {
	print "Catched FileException: ".$e."\n";
}
print "FilesystemException...\n";
try {
	throw new SimpleLion\FilesystemException("/some/dir", "Test message!");
} catch(SimpleLion\FilesystemException $e) {
	print "Catched FilesystemException: ".$e."\n";
}
print "END OF TEST\n";
?>
