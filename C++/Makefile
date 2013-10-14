all:
	g++ -Wall -fPIC -c LocalizationEntry.cpp LocalizationString.cpp LocalizationCategory.cpp Localization.cpp Exceptions.cpp
	g++ -shared -Wl,-soname,libsimplelion.so.0 -o libsimplelion.so.0.1 *.o
install:
	cp libsimplelion.so.0.1 /usr/lib
	mkdir /usr/include/SimpleLion
	cp *.h /usr/include/SimpleLion
	ln -sf /usr/lib/libsimplelion.so.0.1 /usr/lib/libsimplelion.so.0
	ln -sf /usr/lib/libsimplelion.so.0.1 /usr/lib/libsimplelion.so
uninstall:
	rm /usr/lib/libsimplelion.so.0.1
	rm -rf /usr/include/SimpleLion
	rm /usr/lib/libsimplelion.so
	rm /usr/lib/libsimplelion.so.*
clean:
	rm -rf *.so *.so* *.o
test:
	g++ -o LocalizationEntryTest LocalizationEntryTest.cpp LocalizationEntry.cpp
	g++ -o LocalizationStringTest LocalizationStringTest.cpp LocalizationString.cpp LocalizationEntry.cpp
	g++ -o LocalizationCategoryTest LocalizationCategoryTest.cpp LocalizationCategory.cpp LocalizationString.cpp LocalizationEntry.cpp
	g++ -o LocalizationTest LocalizationTest.cpp Localization.cpp LocalizationEntry.cpp LocalizationString.cpp LocalizationCategory.cpp Exceptions.cpp -lboost_filesystem -lboost_system
	g++ -o NoinputLocalizationTest NoinputLocalizationTest.cpp Localization.cpp LocalizationEntry.cpp LocalizationString.cpp LocalizationCategory.cpp Exceptions.cpp -lboost_filesystem -lboost_system
testdebug:
	g++ -o LocalizationEntryTest LocalizationEntryTest.cpp LocalizationEntry.cpp -g
	g++ -o LocalizationStringTest LocalizationStringTest.cpp LocalizationString.cpp LocalizationEntry.cpp -g
	g++ -o LocalizationCategoryTest LocalizationCategoryTest.cpp LocalizationCategory.cpp LocalizationString.cpp LocalizationEntry.cpp -g
	g++ -o LocalizationTest LocalizationTest.cpp Localization.cpp LocalizationEntry.cpp LocalizationString.cpp LocalizationCategory.cpp Exceptions.cpp -lboost_filesystem -lboost_system -g
	g++ -o NoinputLocalizationTest NoinputLocalizationTest.cpp Localization.cpp LocalizationEntry.cpp LocalizationString.cpp LocalizationCategory.cpp Exceptions.cpp -lboost_filesystem -lboost_system -g
testclean:
	rm -rf LocalizationEntryTest LocalizationStringTest LocalizationCategoryTest LocalizationTest NoinputLocalizationTest
