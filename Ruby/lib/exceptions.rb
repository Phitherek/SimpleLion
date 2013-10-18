module SimpleLion
	class FileException < Exception
		def initialize file, msg
			super(file.to_s + ": " + msg.to_s)
		end
	end
	
	class FilesystemException < Exception
		def initialize dir, msg
			super(dir.to_s + ": " + msg.to_s)
		end
	end
end
