require 'socket'
include Socket::Constants

class Client
  public
  def initialize(addr, port)
    @addr = addr
    @port = port
    #@socket = TCPSocket.new @addr, @port 
  end

  def run(input_content)
    while true 
      #  @socket.puts line
      #  @socket.gets line
      #  print line

      input_content.each do |line| 
        put line
      end
    end
  end

  def close
    @socket.close
  end
end

input_content = []
#thd = Thread.new do 
#  client=Client.new('127.0.0.1', 2626)
#  client.run input_content
#end

#thd_input = Thread.new do
#  while true
#    input_content = ARGV.readlines
#  end
#end

#thd.join
#thd_input.join
