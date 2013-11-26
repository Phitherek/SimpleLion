<?php
include("localization.inc.php");
print "SimpleLion PHP module tests - (C) 2013 SimpleLion Development Team\n";
print "Localization (main class) test v.0.1\n";
try {
	chdir('..');
	chdir('locale');
	$dir = getcwd();
	print "Got directory: ".$dir."\n";
	print "Constructing Localization object...\n";
	$loc = new SimpleLion\Localization($dir);
	print "Localization object up and working!\n";
	$locales = $loc->localeList();
	print "Loaded locale list:\n";
	print_r($locales);
	for($i = 0; $i < count($locales); $i++) {
		print "Loading locale: ".$locales[$i]."\n";
		$loc->setLocale($locales[$i]);
		print "test: ".$loc->query("test")."\n";
		print "test2: ".$loc->query("test2")."\n";
		print "test3: ".$loc->query("test3")."\n";
		print "test4: ".$loc->query("test4")."\n";
		print "testcat.test: ".$loc->query("testcat.test")."\n";
		print "testcat.test2: ".$loc->query("testcat.test2")."\n";
		print "testcat.test3: ".$loc->query("testcat.test3")."\n";
		print "testcat.test4: ".$loc->query("testcat.test4")."\n";
		print "testcat.acat.test: ".$loc->query("testcat.acat.test")."\n";
		print "testcat.acat.test2: ".$loc->query("testcat.acat.test2")."\n";
		print "testcat: ".$loc->query("testcat")."\n";
		print "testcat.acat: ".$loc->query("testcat.acat")."\n";
		print "\n";
		print "This locale as SLLF:\n";
		print $loc->toSLLF();
	}
} catch(SimpleLion\FileException $e) {
	print "Caught FileException: ".$e."\n";
} catch(SimpleLion\FilesystemException $e) {
	print "Caught FilesystemException: ".$e."\n";
} catch(Exception $e) {
	print "Caught external Exception: ".$e->getMessage()."\n";
}
print "END OF TEST\n";
?>
