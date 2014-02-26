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
    s.puts line
    s.gets line
    print line
  end

  def close
    s.close
  end
end

client=Client.new
client.run

