<?php
include("localization_category.inc.php");
print "SimpleLion PHP module tests - (C) 2013 SimpleLion Development Team\n";
print "LocalizationCategory test v.0.1\n";
print "Constructing strings and categories...\n";
$s1 = new SimpleLion\LocalizationString("test", "This is test!");
$s2 = new SimpleLIon\LocalizationString("test2", "This is test2!");
$s3 = new SimpleLion\LocalizationString("test", "This is test from acat!");
$s4 = new SimpleLion\LocalizationString("test3", "This is test after acat!");
$c1 = new SimpleLion\LocalizationCategory("testcat");
$c2 = new SimpleLion\LocalizationCategory;
$c2->setName("acat");
print "Constructed:\n";
print "LocalizationString s1: ".$s1->name().":".$s1->value()."\n";
print "LocalizationString s2: ".$s2->name().":".$s2->value()."\n";
print "LocalizationString s3: ".$s3->name().":".$s3->value()."\n";
print "LocalizationString s4: ".$s4->name().":".$s4->value()."\n";
print "LocalizationCategory c1: ".$c1->name()."\n";
print "LocalizationCategory c2: ".$c2->name()."\n";
print "Adding s1 to c1...\n";
$c1->addLocalizationEntry($s1);
print "Adding s2 to c1...\n";
$c1->addLocalizationEntry($s2);
print "Adding s3 to c2...\n";
$c2->addLocalizationEntry($s3);
print "Adding c2 to c1... (yes, this is not a mistake)\n";
$c1->addLocalizationEntry($c2);
print "Adding s4 to c1...\n";
$c1->addLocalizationEntry($s4);
print "Is the c1 valid?\n";
if($c1->valid() == true) {
	print "Yes!\n";
} else {
	print "...Nope...\n";
}
print "Now printing out c1 in SLLF:\n";
print $c1->toSLLF();
print "Ok, so now let' s iterate through c1...\n";
$c1->resetLocalizationEntryIterator();
while(!$c1->localizationEntriesAtEnd()) {
	$e = $c1->getNextLocalizationEntry();
	if($e != null) {
		print $e->toSLLF();
	}
}
print "Now get the element on 1...\n";
$e2 = $c1->getLocalizationEntryAt(1);
print $e2->toSLLF();
print "Now get the element named test3...\n";
$e3 = $c1->getLocalizationEntryByName("test3");
print $e3->toSLLF();
print "Now get the element on 10...\n";
$e4 = $c1->getLocalizationEntryAt(10);
if($e4 == null) {
	print "...Ok, it' s null.\n";
} else {
	print "...Nope...\n";
}
print "Now get the element named blah...\n";
$e5 = $c1->getLocalizationEntryByName("blah");
if($e5 == null) {
	print "...Ok, it' s null.\n";
} else {
	print "...Nope...\n";
}
print "Now remove the element on 1...\n";
$res = $c1->removeLocalizationEntry(1);
if($res == true) {
	print "Removed!\n";
	print $c1->toSLLF();
} else {
	print "...Nope...\n";
}
print "Now remove the element on 10...\n";
$res = $c1->removeLocalizationEntry(10);
if($res == false) {
	print "Ok, not removed!\n";
} else {
	print "...Nope...\n";
}
print "Now remove the element named test3...\n";
$res = $c1->removeLocalizationEntryByName("test3");
if($res == true) {
	print "Removed!\n";
	print $c1->toSLLF();
} else {
	print "...Nope...\n";
}
print "Now remove the element named blah...\n";
$res = $c1->removeLocalizationEntryByName("blah");
if($res == false) {
	print "Ok, not removed!\n";
} else {
	print "...Nope...\n";
}
print "And for the last checks, let' s mess around with the invalid c3 object!\n";
$c3 = new SimpleLion\LocalizationCategory;
print "Ok, so the c3 should be invalid...\n";
if($c3->valid() == false) {
	print "And it is!\n";
} else {
	print "...Nope...\n";
}
print "Now, I want to add s1 to c3...\n";
$res = $c3->addLocalizationEntry($s1);
if($res == false) {
	print "Ok, it does not let me...\n";
} else {
	print "...Nope...\n";
}
print "So the name should be null...\n";
$res = $c3->name();
if($res == null) {
	print "And it is!\n";
} else {
	print "...Nope...\n";
}
print "And last but not least, the SLLF should be null...\n";
$res = $c3->toSLLF();
if($res == null) {
	print "And it is!\n";
} else {
	print "...Nope...\n";
}
print "END OF TEST\n";
?>
