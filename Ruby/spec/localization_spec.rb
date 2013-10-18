require 'localization'
require 'spec_helper'

describe SimpleLion::Localization do
	it 'should fail when given directory that does not exist and cannot be created' do
		expect { SimpleLion::Localization.new("/test") }.to raise_exception(SimpleLion::FilesystemException, '/test: Not a valid directory and cannot be created!')
	end
	it 'should fail when given directory that does not exist and is just created or has no files' do
		expect { SimpleLion::Localization.new("test") }.to raise_exception(SimpleLion::FilesystemException, 'test: No SLLF files present!')
		expect { SimpleLion::Localization.new("test") }.to raise_exception(SimpleLion::FilesystemException, 'test: No SLLF files present!')
		Dir.rmdir('test').should be_true
	end
	it 'should create when the directory is OK and has at least one SLLF file in it' do
		l = SimpleLion::Localization.new("../locale")
	end
	it 'should fail when there is no such locale' do
		expect { SimpleLion::Localization.new("../locale", "sth") }.to raise_exception(SimpleLion::FileException, "../locale/sth.sllf: No such locale!")
	end
	it 'should create and load existing locale' do
		l = SimpleLion::Localization.new("../locale", "en")
	end
	it 'should not fail but return error messages to output on parse errors' do
		l = SimpleLion::Localization.new("../locale", "fail")
	end
	
	describe 'setLocale' do
		it 'should fail when there is no such locale' do
			l = SimpleLion::Localization.new("../locale")
			expect { l.setLocale("sth") }.to raise_exception(SimpleLion::FileException, "../locale/sth.sllf: No such locale!")
		end
		it 'should load existing locale' do
			l = SimpleLion::Localization.new("../locale")
			l.setLocale("en")
		end
		it 'should not fail but return error messages to output on parse errors' do
			l = SimpleLion::Localization.new("../locale")
			l.setLocale("fail")
		end
		it 'should correctly change locale' do
			l = SimpleLion::Localization.new("../locale", "en")
			l.query("test").should eq("Test string")
			l.setLocale("pl")
			l.query("test").should eq("Testowy string")
		end
	end
	
	describe 'query' do
		it 'should return appropriate messages on nil or empty query' do
			l = SimpleLion::Localization.new("../locale")
			l.query(nil).should eq("simplelion:err:invalid_query: nil")
			l.query("").should eq("simplelion:err:invalid_query: empty")
		end
		it 'should return appropriate message when no locale loaded' do
			l = SimpleLion::Localization.new("../locale")
			l.query("sth").should eq("simplelion:err:no_locale")
		end
		it 'should return appropriate message on invalid query format' do
			l = SimpleLion::Localization.new("../locale", "en")
			l.query(".sth").should eq("simplelion:err:invalid_query: .sth")
		end
		it 'should return appropriate message when translation is missing' do
			l = SimpleLion::Localization.new("../locale", "en")
			l.query("test4").should eq("simplelion:err:translation_missing: test4")
			l.query("testcat.test4").should eq("simplelion:err:translation_missing: testcat.test4")
			l.query("testcat.acat.test2").should eq("simplelion:err:translation_missing: testcat.acat.test2")
			l.query("testcat").should eq("simplelion:err:translation_missing: testcat")
			l.query("testcat.acat").should eq("simplelion:err:translation_missing: testcat.acat")
			l.setLocale("en")
			l.query("test4").should eq("simplelion:err:translation_missing: test4")
			l.query("testcat.test4").should eq("simplelion:err:translation_missing: testcat.test4")
			l.query("testcat.acat.test2").should eq("simplelion:err:translation_missing: testcat.acat.test2")
			l.query("testcat").should eq("simplelion:err:translation_missing: testcat")
			l.query("testcat.acat").should eq("simplelion:err:translation_missing: testcat.acat")
		end
		it 'should return localized string value' do
			l = SimpleLion::Localization.new("../locale", "en")
			l.query("test").should eq("Test string")
			l.query("test2").should eq("Another test string")
			l.query("test3").should eq("Test global string after testcat")
			l.query("testcat.test").should eq("Test string from testcat")
			l.query("testcat.test2").should eq("Another test string from testcat")
			l.query("testcat.test3").should eq("Test string from testcat after acat")
			l.query("testcat.acat.test").should eq("Test string from testcat -> acat")
			l.setLocale("en")
			l.query("test").should eq("Test string")
			l.query("test2").should eq("Another test string")
			l.query("test3").should eq("Test global string after testcat")
			l.query("testcat.test").should eq("Test string from testcat")
			l.query("testcat.test2").should eq("Another test string from testcat")
			l.query("testcat.test3").should eq("Test string from testcat after acat")
			l.query("testcat.acat.test").should eq("Test string from testcat -> acat")
		end
	end
	
	describe "localeList" do
		it 'should return correct locale list' do
			l = SimpleLion::Localization.new("../locale")
			locales = l.localeList
			locales.include?("en").should be_true
			locales.include?("pl").should be_true
			locales.include?("fail").should be_true
		end
	end
	
	describe "toSLLF" do
		it 'should return nil when file empty' do
			l = SimpleLion::Localization.new("../locale")
			l.toSLLF.should be_nil
		end
		it 'should return good SLLF format' do
			l = SimpleLion::Localization.new("../locale", "en")
			file = ""
			File.open("../locale/en.sllf") do |fh|
				fh.readlines.each do |line|
					file += line
				end
			end
			l.toSLLF.should eq(file)
		end
	end
end
