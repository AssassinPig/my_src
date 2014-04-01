require 'socket'
include Socket::Constants

class Client
  public
  def initialize(addr, port)
    @addr = addr
    @port = port
    @socket = TCPSocket.new @addr, @port 
  end

  def run
    while 1
      @socket.puts line
      @socket.gets line
      print line
    end
  end

  def close
    @socket.close
  end
end

client=Client.new('', 2626)
client.run

