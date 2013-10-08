all:
	g++ -o LocalizationEntryTest LocalizationEntryTest.cpp LocalizationEntry.cpp
	g++ -o LocalizationStringTest LocalizationStringTest.cpp LocalizationString.cpp LocalizationEntry.cpp
	g++ -o LocalizationCategoryTest LocalizationCategoryTest.cpp LocalizationCategory.cpp LocalizationString.cpp LocalizationEntry.cpp
debug:
	g++ -o LocalizationEntryTest LocalizationEntryTest.cpp LocalizationEntry.cpp -g
	g++ -o LocalizationStringTest LocalizationStringTest.cpp LocalizationString.cpp LocalizationEntry.cpp
	g++ -o LocalizationCategoryTest LocalizationCategoryTest.cpp LocalizationCategory.cpp LocalizationString.cpp LocalizationEntry.cpp -g
clean:
	rm -rf LocalizationEntryTest LocalizationStringTest LocalizationCategoryTest
