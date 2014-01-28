#!/ruby/bin/ruby
require 'cgi'
print "Content-type: text/html \n\n"
cgi = CGI.new
print "Name = "
print cgi['Name']
print"<br>"
print"<br>"
print "Type = "
print cgi['Type']

