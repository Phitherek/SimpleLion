all:
	g++ -o LocalizationEntryTest LocalizationEntryTest.cpp LocalizationEntry.cpp
	g++ -o LocalizationStringTest LocalizationStringTest.cpp LocalizationString.cpp LocalizationEntry.cpp
	g++ -o LocalizationCategoryTest LocalizationCategoryTest.cpp LocalizationCategory.cpp LocalizationString.cpp LocalizationEntry.cpp
	g++ -o LocalizationTest LocalizationTest.cpp Localization.cpp LocalizationEntry.cpp LocalizationString.cpp LocalizationCategory.cpp Exceptions.cpp -lboost_filesystem -lboost_system
	g++ -o NoinputLocalizationTest NoinputLocalizationTest.cpp Localization.cpp LocalizationEntry.cpp LocalizationString.cpp LocalizationCategory.cpp Exceptions.cpp -lboost_filesystem -lboost_system
debug:
	g++ -o LocalizationEntryTest LocalizationEntryTest.cpp LocalizationEntry.cpp -g
	g++ -o LocalizationStringTest LocalizationStringTest.cpp LocalizationString.cpp LocalizationEntry.cpp -g
	g++ -o LocalizationCategoryTest LocalizationCategoryTest.cpp LocalizationCategory.cpp LocalizationString.cpp LocalizationEntry.cpp -g
	g++ -o LocalizationTest LocalizationTest.cpp Localization.cpp LocalizationEntry.cpp LocalizationString.cpp LocalizationCategory.cpp Exceptions.cpp -lboost_filesystem -lboost_system -g
	g++ -o NoinputLocalizationTest NoinputLocalizationTest.cpp Localization.cpp LocalizationEntry.cpp LocalizationString.cpp LocalizationCategory.cpp Exceptions.cpp -lboost_filesystem -lboost_system
clean:
	rm -rf LocalizationEntryTest LocalizationStringTest LocalizationCategoryTest LocalizationTest NoinputLocalizationTest
