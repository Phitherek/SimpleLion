module SimpleLion
	class LocalizationString
		def initialize name=nil, value=nil
			@name = name.to_s
			@value = value.to_s
		end
		def valid?
			!(@name == nil || @name.empty? || @value == nil || @value.empty?)
		end
		def name
			@name.to_sym
		end
		def value
			@value
		end
		def setName name
			@name = name.to_s
		end
		def setValue value
			@value = value.to_s
		end
		def toSLLF
			if self.valid?
				"[" + @name + "]\n" + @value + "\n"
			else
				nil
			end
		end
	end
end
