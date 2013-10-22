<?php
include("localization_string.inc.php");
print "SimpleLion PHP module tests - (C) 2013 SimpleLion Development Team\n";
print "LocalizationString test v. 0.1\n";
print "Constructing a LocalizationString...\n";
$l = new SimpleLion\LocalizationString("test", "Test string!");
print "Constructed a LocalizationString: ".$l->name().":".$l->value()."\n";
print "Its representation in SLLF is:\n";
print $l->toSLLF();
print "Changing a LocalizationString...\n";
$l->setName("atest");
$l->setValue("Another test string value!");
print "LocalizationString after change: ".$l->name().":".$l->value()."\n";
print "Its representation in SLLF is:\n";
print $l->toSLLF();
print "END OF TEST\n";
?>
