module SimpleLion
	
	##
	# A class that represents localized string
	
	class LocalizationString
		
		##
		# A constructor, that initializes the string with +name+ identifier and +value+ in current locale
		#
		# +name+ and +value+ can be nil, but the constructed string is invalid then and has to be filled in later
		
		def initialize name=nil, value=nil
			@name = name.to_s
			@value = value.to_s
		end
		
		##
		# A method that returns if the string is valid, which means it is filled with non-empty name and value
		
		def valid?
			!(@name == nil || @name.empty? || @value == nil || @value.empty?)
		end
		
		##
		# A method that returns name of the string as a symbol
		
		def name
			@name.to_sym
		end
		
		##
		# A method that returns localized value of the string
		
		def value
			@value
		end
		
		##
		# A method that sets name of the string to +name+
		
		def setName name
			@name = name.to_s
		end
		
		##
		# A method that sets localized value of the string to +value+
		
		def setValue value
			@value = value.to_s
		end
		
		##
		# A method that outputs the string in SLLF format
		
		def toSLLF
			if self.valid?
				"[" + @name + "]\n" + @value + "\n"
			else
				nil
			end
		end
	end
end
