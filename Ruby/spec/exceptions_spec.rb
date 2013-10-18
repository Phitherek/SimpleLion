require 'exceptions'
require 'spec_helper'

describe SimpleLion::FileException do
	it 'should return a valid message' do
		e = SimpleLion::FileException.new("/sample/file/path.ext", "Test")
		e.to_s.should eq("/sample/file/path.ext: Test")
	end
end

describe SimpleLion::FilesystemException do
	it 'should return a valid message' do
		e = SimpleLion::FileException.new("/sample/dir/path", "Test")
		e.to_s.should eq("/sample/dir/path: Test")
	end
end
