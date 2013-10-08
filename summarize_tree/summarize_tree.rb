#!/usr/bin/ruby

require 'find'

### Create variables counting each. ###

dir = ARGV[0]
directCount = 0
Find.find(dir) do |path|
  if FileTest.directory?(path)
    directCount += 1
  end
end
fileCount = Dir["#{ARGV[0]}/**/*"].length



puts "Processed all the files from <#{dir}>"
puts "There were #{directCount} directories."
puts "There were #{fileCount} regular files."

