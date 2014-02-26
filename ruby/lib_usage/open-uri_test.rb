require 'open-uri'
require 'httpclient'

URL="http://www.ruby-lang.org/en"

httpclient=HTTPClient.new
resp=httpclient.get(URL)
puts resp.header['Location']

#open("http://www.ruby-lang.org/en") do |f| 
#  begin
#    f.each_line {|line| print line}
#
#  rescue OpenURI::HTTPRedirect
#    puts "Redirect" 
#    raise
#
#    puts f.base_uri
#    puts f.content_type
#    puts f.charset
#    puts f.content_encoding
#    puts f.content_encoding
#    puts f.last_modified
#  end
#
#end
