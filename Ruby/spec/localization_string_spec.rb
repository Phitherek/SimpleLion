require 'spec_helper'
require 'localization_string'

describe SimpleLion::LocalizationString do
	it "should be constructed empty and invalid by default" do
		s = SimpleLion::LocalizationString.new
		s.valid?.should be_false
	end
	it "should be constructed with correct name and value, have working getters and be valid" do
		s = SimpleLion::LocalizationString.new(:test, "Test value!")
		s.valid?.should be_true
		s.name.should eq(:test)
		s.value.should eq("Test value!")
	end
	it "should have working setters" do
		s = SimpleLion::LocalizationString.new
		s.setName(:test)
		s.name.should eq(:test)
		s.setValue("Test value!")
		s.value.should eq("Test value!")
		s.valid?.should be_true
	end
	it "should be invalid when one of the fields is empty" do
		s = SimpleLion::LocalizationString.new
		s.valid?.should be_false
		s.setName(:test)
		s.valid?.should be_false
		s.setName(nil)
		s.setValue("Test value!")
		s.valid?.should be_false
	end
	it "should return nil when queried for SLLF conversion on invalid string" do
		s = SimpleLion::LocalizationString.new
		s.toSLLF.should be_nil
		s.setName(:test)
		s.toSLLF.should be_nil
		s.setName(nil)
		s.setValue("Test value!")
		s.toSLLF.should be_nil
	end
	
	it "should return correct SLLF format from SLLF conversion function" do
		s = SimpleLion::LocalizationString.new(:name, "Test value!")
		s.toSLLF.should eq("[name]\nTest value!\n")
	end
end
