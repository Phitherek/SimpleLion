module SimpleLion
	
	##
	# This is an exception that is raised when there is a problem with the localization file - mostly when it does not exist
	
	class FileException < Exception
		
		##
		# This constructor initializes the exception with error message that states which +file+ the script was trying to open and what happened - by +msg+
		
		def initialize file, msg
			super(file.to_s + ": " + msg.to_s)
		end
	end
	
	##
	# This is an exception that is raised when there is a problem with the directory - it is either unaccessible, cannot be created or does not have any SLLF localization file inside
	
	class FilesystemException < Exception
		
		##
		# This constructor initializes the exception with error message that states which +dir+ the script was trying to process and what happened - by +msg+
		
		def initialize dir, msg
			super(dir.to_s + ": " + msg.to_s)
		end
	end
end
