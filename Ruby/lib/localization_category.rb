require 'localization_string'

module SimpleLion
	class LocalizationCategory
		def initialize name=nil
			@name = name
			@subentries = []
			@subentriesIterator = -1
			@subentriesEnd = true
		end
		def valid?
			!(@name == nil || @name.empty?)
		end
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
		def getLocalizationEntryAt idx
			if idx < @subentries.count
				return @subentries[idx]
			else
				nil
			end
		end
		def removeLocalizationEntry idx
			if idx < @subentries.count
				@subentries.delete_at(idx)
				true
			else
				false
			end
		end
		def getLocalizationEntryByName name
			@subentries.each do |subentry|
				if subentry.name == name
					return subentry
				end
			end
			return nil
		end
		def removeLocalizationEntryByName name
			@subentries.each do |subentry|
				if subentry.name == name
					@subentries.delete(subentry)
					return true
				end
			end
			return false
		end
		def name
			@name.to_sym
		end
		def resetLocalizationEntryIterator
			@subentriesIterator = -1
			if @subentries.count > 0
				@subentriesEnd = false
			else
				@subentriesEnd = true
			end
		end
		def localizationEntriesAtEnd?
			@subentriesEnd
		end
		def setName name
			@name = name.to_s
		end
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
