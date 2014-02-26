#! /usr/bin/env ruby
ARGV.each  do |file|
  input_file = File.open(file, "r")
  contents = input_file.read()
  input_file.close()

  output_filename = file.gsub(".txt","_new.txt")
  output_file = File.open(output_filename, "w+")
  output_file.puts(contents)
  output_file.close()
end
