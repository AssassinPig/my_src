require "socket"
include Socket::Constants

#class Client
#	public
#	def initialize(addr, port)
#	end
#
#	def run
#	end
#end

#client=Client.new
#client.run

n=0
line="get"
#while 1 
#s = TCPSocket.new '127.0.0.1', 27149 
#print "puts \n", n
#s.puts line
#line = s.gets 
#n = n+1
#s.close
#break if n==100 
#end

s = TCPSocket.new '127.0.0.1', 27149 
s.puts line
s.gets line
print line
s.close
