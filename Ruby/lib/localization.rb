require 'localization_string'
require 'localization_category'
require 'exceptions'

module SimpleLion
	class Localization
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
