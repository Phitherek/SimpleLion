require 'spec_helper'
require 'localization_category'

describe SimpleLion::LocalizationCategory do
	it 'should be invalid and have certain parameters by default' do
		c = SimpleLion::LocalizationCategory.new
		c.valid?.should be_false
		c.localizationEntriesAtEnd?.should be_true
		c.toSLLF.should be_nil
	end
	it 'should be valid when constructed with name and have certain parameters' do
		c = SimpleLion::LocalizationCategory.new(:testcat)
		c.valid?.should be_true
		c.localizationEntriesAtEnd?.should be_true
		c.toSLLF.should_not be_nil
		c.toSLLF.should eq("{testcat}\n{end}\n")
	end
	describe 'addLocalizationEntry' do
		it 'should correctly add LocalizationString' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			s = SimpleLion::LocalizationString.new(:test, "Test string!")
			c.addLocalizationEntry(s).should be_true
			c.localizationEntriesAtEnd?.should be_false
			c.getLocalizationEntryAt(0).should eq(s)
		end
		it 'should correctly add LocalizationCategory' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			c2 = SimpleLion::LocalizationCategory.new(:acat)
			c.addLocalizationEntry(c2).should be_true
			c.localizationEntriesAtEnd?.should be_false
			c.getLocalizationEntryAt(0).should eq(c2)
		end
		it 'should not add invalid LocalizationString' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			s = SimpleLion::LocalizationString.new
			c.addLocalizationEntry(s).should be_false
			c.localizationEntriesAtEnd?.should be_true
			c.getLocalizationEntryAt(0).should be_nil
		end
		it 'should not add invalid LocalizationCategory' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			c2 = SimpleLion::LocalizationCategory.new
			c.addLocalizationEntry(c2).should be_false
			c.localizationEntriesAtEnd?.should be_true
			c.getLocalizationEntryAt(0).should be_nil
		end
		it 'should not add to invalid LocalizationCategory' do
			c = SimpleLion::LocalizationCategory.new
			c2 = SimpleLion::LocalizationCategory.new(:acat)
			c.addLocalizationEntry(c2).should be_false
			c.localizationEntriesAtEnd?.should be_true
			c.getLocalizationEntryAt(0).should be_nil
		end
	end
	describe "getNextLocalizationEntry" do
		it 'should return nil on empty subentries' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			c.getNextLocalizationEntry.should be_nil
		end
		it 'should always return next subentry or nil at end' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			s = SimpleLion::LocalizationString.new(:test, "Test string!")
			c2 = SimpleLion::LocalizationCategory.new(:acat)
			c.addLocalizationEntry(s).should be_true
			c.addLocalizationEntry(c2).should be_true
			c.localizationEntriesAtEnd?.should_not be_true
			c.getNextLocalizationEntry.should eq(s)
			c.localizationEntriesAtEnd?.should_not be_true
			c.getNextLocalizationEntry.should eq(c2)
			c.localizationEntriesAtEnd?.should_not be_true
			c.getNextLocalizationEntry.should be_nil
			c.localizationEntriesAtEnd?.should be_true
		end
	end
	describe "getLocalizationEntryAt" do
		it 'should return relevant subentry' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			s = SimpleLion::LocalizationString.new(:test, "Test string!")
			c2 = SimpleLion::LocalizationCategory.new(:acat)
			c.addLocalizationEntry(s).should be_true
			c.addLocalizationEntry(c2).should be_true
			c.getLocalizationEntryAt(0).should eq(s)
			c.getLocalizationEntryAt(1).should eq(c2)
		end
		it 'should return nil if no subentry or out of range' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			c.getLocalizationEntryAt(0).should be_nil
			s = SimpleLion::LocalizationString.new(:test, "Test string!")
			c2 = SimpleLion::LocalizationCategory.new(:acat)
			c.addLocalizationEntry(s).should be_true
			c.addLocalizationEntry(c2).should be_true
			c.getLocalizationEntryAt(2).should be_nil
		end
	end
	describe "removeLocalizationEntry" do
		it 'should remove relevant subentry' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			s = SimpleLion::LocalizationString.new(:test, "Test string!")
			c2 = SimpleLion::LocalizationCategory.new(:acat)
			c.addLocalizationEntry(s).should be_true
			c.addLocalizationEntry(c2).should be_true
			c.removeLocalizationEntry(0).should be_true
			c.getLocalizationEntryAt(0).should eq(c2)
		end
		it 'should return nil if no subentry' do
			c = SimpleLion::LocalizationCategory.new(:testcat)
			c.removeLocalizationEntry(0).should be_false
			s = SimpleLion::LocalizationString.new(:test, "Test string!")
			c2 = SimpleLion::LocalizationCategory.new(:acat)
			c.addLocalizationEntry(s).should be_true
			c.addLocalizationEntry(c2).should be_true
			c.removeLocalizationEntry(2).should be_false
		end
	end
end
