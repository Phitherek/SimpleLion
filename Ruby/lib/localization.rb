require 'localization_string'
require 'localization_category'
require 'exceptions'

##
# ==The SimpleLion module for Ruby
#
# SimpleLion is a multi-language, simple localization framework inspired by Ruby on Rails localization engine. This is a language-specific module for Ruby.
#
# The basic information on the project and wiki can be (for now) found at http://redmine.phitherek.mooo.com and you can also contribute for the project there!

module SimpleLion
	
	##
	# This is the main class of the SimpleLion module for Ruby. It handles parsing, storing and querying data from SLLF files.
	
	class Localization
		
		##
		# This constructor initializes Localization object with data from given +path+ and +locale+
		#
		# +locale+ can be nil, only list of available locales is loaded then
		#
		# It raises FilesystemException when there is a problem with the directory (it can' t open or create it or it has no locale files inside)
		#
		# It raises FileException when the selected locale file does not exist
		#
		# The SLLF Parser inside the constructor outputs warnings if the SLLF file format is wrong in some place, it also outputs the line number where the problem exists
		
		def initialize path, locale=nil
			if File.directory?(path)
				@basepath = path
			else
				begin
					Dir.mkdir(path)
				rescue
					raise SimpleLion::FilesystemException.new(path, "Not a valid directory and cannot be created!")
				end
				@basepath = path
			end
			@locales = []
			basedir = Dir.new(@basepath)
			basedir.each do |fn|
				if File.file?(@basepath + "/" + fn) && fn.split('.')[1] == 'sllf'
					@locales << File.basename(fn, ".sllf")
				end
			end
			if @locales.empty?
				raise SimpleLion::FilesystemException.new(@basepath, "No SLLF files present!")
			end
			if locale != nil
				if !@locales.include?(locale)
					raise SimpleLion::FileException.new(@basepath + "/" + locale + ".sllf", "No such locale!")
				end
				@locale = locale
				@file = []
				filepath = @basepath + "/" + @locale + ".sllf"
				File.open(filepath) do |fh|
					name = ""
					value = ""
					category = nil
					categories = []
					i = 0
					fh.readlines.each do |line|
						line.strip!
						i = i+1
						if line[0] == '['
							if !name.empty?
								puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Not adding previous string because found the beginning of another string declaration!\n"
							end
							parsed = line.partition("[").last.partition("]").first
							sep1 = line.partition("[")[1]
							sep2 = line.partition("[").last.partition("]")[1]
							if sep1.empty? || sep2.empty?
								parsed = ""
							end
							if parsed.empty?
								puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Skipping invalid/empty string declaration!\n"
							end
							name = parsed
						elsif line[0] == '{'
							parsed = line.partition("{").last.partition("}").first
							sep1 = line.partition("{")[1]
							sep2 = line.partition("{").last.partition("}")[1]
							if sep1.empty? || sep2.empty?
								parsed = ""
							end
							if parsed.empty?
								puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Skipping invalid/empty category declaration!\n"
							else
								if parsed == "end"
									if category == nil
										puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Encountered end-of-category not matching to a category! Skipping...\n"
									else
										tmpcat = category
										category = categories.pop
										if category == nil
											@file << tmpcat
										else
											category.addLocalizationEntry(tmpcat)
										end

									end
								else
									if category != nil
										categories << category
									end
									category = SimpleLion::LocalizationCategory.new(parsed)
								end
							end
						else
							value = line
							if name.empty?
								puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Skipping value of invalid/empty string declaration!\n"
							else
								if value.empty?
									puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Skipping empty value of string!\n"
								else
									str = SimpleLion::LocalizationString.new(name, value)
									if category == nil
										@file << str
									else
										category.addLocalizationEntry(str)
									end
								end
							end
							name = ""
							value = ""
						end
					end
				end
			end
		end
		
		##
		# This method loads or changes locale in the Localization object. The SLLF locale file is loaded, parsed and stored inside the object
		#
		# It raises FilesystemException when there are no locales in the base directory of the Localization object
		#
		# It raises FileException when the selected locale file does not exist
		#
		# The SLLF Parser inside the method outputs warnings if the SLLF file format is wrong in some place, it also outputs the line number where the problem exists
		
		def setLocale locale
			@locales = []
			basedir = Dir.new(@basepath)
			basedir.each do |fn|
				if File.file?(@basepath + "/" + fn) && fn.split('.')[1] == 'sllf'
					@locales << File.basename(fn, ".sllf")
				end
			end
			if @locales.empty?
				raise SimpleLion::FilesystemException.new(@basepath, "No SLLF files present!")
			end
			if locale != nil
				if !@locales.include?(locale)
					raise SimpleLion::FileException.new(@basepath + "/" + locale + ".sllf", "No such locale!")
				end
				@locale = locale
				@file = []
				filepath = @basepath + "/" + @locale + ".sllf"
				File.open(filepath) do |fh|
					name = ""
					value = ""
					category = nil
					categories = []
					i = 0
					fh.readlines.each do |line|
						line.strip!
						i = i+1
						if line[0] == '['
							if !name.empty?
								puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Not adding previous string because found the beginning of another string declaration!\n"
							end
							parsed = line.partition("[").last.partition("]").first
							sep1 = line.partition("[")[1]
							sep2 = line.partition("[").last.partition("]")[1]
							if sep1.empty? || sep2.empty?
								parsed = ""
							end
							if parsed.empty?
								puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Skipping invalid/empty string declaration!\n"
							end
							name = parsed
						elsif line[0] == '{'
							parsed = line.partition("{").last.partition("}").first
							sep1 = line.partition("{")[1]
							sep2 = line.partition("{").last.partition("}")[1]
							if sep1.empty? || sep2.empty?
								parsed = ""
							end
							if parsed.empty?
								puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Skipping invalid/empty category declaration!\n"
							else
								if parsed == "end"
									if category == nil
										puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Encountered end-of-category not matching to a category! Skipping...\n"
									else
										tmpcat = category
										category = categories.pop
										if category == nil
											@file << tmpcat
										else
											category.addLocalizationEntry(tmpcat)
										end

									end
								else
									if category != nil
										categories << category
									end
									category = SimpleLion::LocalizationCategory.new(parsed)
								end
							end
						else
							value = line
							if name.empty?
								puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Skipping value of invalid/empty string declaration!\n"
							else
								if value.empty?
									puts "SLLF Parser: " + File.basename(filepath) + ":" + i.to_s + " WARNING: Skipping empty value of string!\n"
								else
									str = SimpleLion::LocalizationString.new(name, value)
									if category == nil
										@file << str
									else
										category.addLocalizationEntry(str)
									end
								end
							end
							name = ""
							value = ""
						end
					end
				end
			end
		end
		
		##
		# This method queries the Localization object for the localized value of the string according to +queryString+
		#
		# The queryString has format: string_name or category_name.category_name.(...).string_name - (...) means n more category names
		#
		# It returns the value of the string found with +queryString+ in current locale or error message:
		# * simplelion:err:invalid_query - if there is a problem with the query
		# * simplelion:err:no_locale - if no locale is loaded
		# * simplelion:err:translation_missing - if no string could be found that matches given +queryString+
		# These error messages are returned as a string value, so they will eventually be displayed in the place of missing/invalid localized strings
		
		def query queryString
			if queryString == nil
				return "simplelion:err:invalid_query: nil"
			end
			if queryString.empty?
				return "simplelion:err:invalid_query: empty"
			end
			splittedQuery = queryString.split('.')
			if @file == nil || @file.empty?
				return "simplelion:err:no_locale"
			end
			cat = nil
			splittedQuery.each do |curr|
				if curr == ""
					return "simplelion:err:invalid_query: " + queryString
				else
					if cat == nil
						found = false
						@file.each do |entry|
							if entry.name.to_s == curr
								if splittedQuery.last == curr
									if entry.is_a?(SimpleLion::LocalizationString)
										return entry.value
									end
								else
									if entry.is_a?(SimpleLion::LocalizationCategory)
										cat = entry
										found = true
									end
								end
							end
						end
						if !found
							return "simplelion:err:translation_missing: " + queryString
						end
					else
						entry = cat.getLocalizationEntryByName curr
						if entry == nil
							return "simplelion:err:translation_missing: " + queryString
						end
						if splittedQuery.last == curr
							if entry.is_a?(SimpleLion::LocalizationString)
								return entry.value
							else
								return "simplelion:err:translation_missing: " + queryString
							end
						else
							if entry.is_a?(SimpleLion::LocalizationCategory)
								cat = entry
							else
								return "simplelion:err:translation_missing: " + queryString
							end
						end
					end
				end
			end
		end
		
		##
		# This method returns an array of available locale codes
		#
		# Every run of this method refreshes the available locale list and so its output is always up-to-date
		#
		# It can also return empty list, but it should not happen because the constructor takes care of locale presence
		
		def localeList
			@locales = []
			basedir = Dir.new(@basepath)
			basedir.each do |fn|
				if File.file?(@basepath + "/" + fn) && fn.split('.')[1] == 'sllf'
					@locales << File.basename(fn, ".sllf")
				end
			end
			@locales
		end
		
		##
		# This method outputs the Localization in the SLLF format - it is identical that parsed file unless the Localization object has been modified in some way in the script
		#
		# It returns nil if no locale file has been loaded
		
		def toSLLF
			if @file == nil || @file.empty?
				nil
			else
				out = ""
				@file.each do |entry|
					out += entry.toSLLF
				end
				out
			end
		end
	end
end
