require 'localization_string'

module SimpleLion
	
	##
	# A class that represents a category grouping localized strings
	
	class LocalizationCategory
		
		##
		# A constructor that initializes class with +name+ - identifier for the category
		#
		# +name+ can be nil, but the constructed category will be invalid and will have to be filled in later
		
		def initialize name=nil
			@name = name
			@subentries = []
			@subentriesIterator = -1
			@subentriesEnd = true
		end
		
		##
		# A method that checks if the category is valid which means it is filled with non-empty name
		
		def valid?
			!(@name == nil || @name.empty?)
		end
		
		##
		# A method that adds LocalizationString or LocalizationCategory +entry+ to the category. That way there can be inifitely nested categories with strings and other categories in them, which is a perfect structure to store the SLLF file data in
		#
		# It returns true on success and false on failure
		
		def addLocalizationEntry entry
			if self.valid?
				if entry.valid?
					@subentries << entry
					if @subentriesEnd && @subentriesIterator < @subentries.count
						@subentriesEnd = false
					end
					true
				else
					false
				end
			else
				false
			end
		end
		
		##
		# A method that gets next LocalizationString or LocalizationCategory from the category, referring to the iterator of subentries array
		#
		# It returns appropriate LocalizationString or LocalizationCategory and nil if the iterator reaches the end of the subentries array
		
		def getNextLocalizationEntry
			if !@subentriesEnd
				@subentriesIterator = @subentriesIterator+1
				if @subentriesIterator < @subentries.count
					return @subentries[@subentriesIterator]
				else
					@subentriesEnd = true
					nil
				end
			else
				nil
			end
		end
		
		##
		# A method that gets LocalizationString or LocalizationCategory from the category from given +idx+ and returns it or nil if there is no string nor category under that index
		
		def getLocalizationEntryAt idx
			if idx < @subentries.count
				return @subentries[idx]
			else
				nil
			end
		end
		
		##
		# A method that removes LocalizationString or LocalizationCategory from the category from given +idx+ and returns true on success, false on failure
		
		def removeLocalizationEntry idx
			if idx < @subentries.count
				@subentries.delete_at(idx)
				true
			else
				false
			end
		end
		
		##
		# A method that gets LocalizationString or LocalizationCategory from the category by given +name+ and returns it or nil if there is no string nor category with this name
		
		def getLocalizationEntryByName name
			@subentries.each do |subentry|
				if subentry.name.to_s == name.to_s
					return subentry
				end
			end
			return nil
		end
		
		##
		# A method that removes LocalizationString or LocalizationCategory from the category by given +name+ and returns true on success, false on failure
		
		def removeLocalizationEntryByName name
			@subentries.each do |subentry|
				if subentry.name.to_s == name.to_s
					@subentries.delete(subentry)
					return true
				end
			end
			return false
		end
		
		##
		# A method that returns name of the category as a symbol or nil if there is no name
		
		def name
			if @name != nil
				@name.to_sym
			else
				nil
			end
		end
		
		##
		# A method that resets subentries array iterator to the beginning of the array
		
		def resetLocalizationEntryIterator
			@subentriesIterator = -1
			if @subentries.count > 0
				@subentriesEnd = false
			else
				@subentriesEnd = true
			end
		end
		
		##
		# A method that returns if subentries array iterator has reached the end of the array
		
		def localizationEntriesAtEnd?
			@subentriesEnd
		end
		
		##
		# A method that sets name of the category to +name+
		
		def setName name
			@name = name.to_s
		end
		
		##
		# A method that returns category and all its subentries in the SLLF format or nil if the category is not valid
		
		def toSLLF
			if self.valid?
				str = "{" + @name.to_s + "}\n"
				@subentries.each do |subentry|
					if subentry.valid?
						str += subentry.toSLLF
					end
				end
				str += "{end}\n"
			else
				nil
			end
		end
	end
end
