require "socket"
include Socket::Constants   

class ChatServer
  public 
  def initialize(ip, port)
    @ip = ip
    @descriptors = Array::new
    @serverSocket = TCPServer::new(ip, port)
    @serverSocket.setsockopt(Socket::SOL_SOCKET, Socket::SO_REUSEADDR, 1)	
    printf "Chat server started on port%d\n", port
    @descriptors.push(@serverSocket)
  end #initialize

  def run
    while true 
      res = select(@descriptors, nil, nil, nil)
      if res != nil then
        for sock in res[0]
          if sock == @serverSocket then
            accept_new_connection	
          else 	
            if sock.eof? then
              str = sprintf("client left %s:%s\n",
                            sock.peeraddr[2], sock.peeraddr[1])
              broadcast_string(str, sock)
              sock.close
              @descriptors.delete(sock)
            else
              str = sprintf("[%s|%s]:%s\n",
                            sock.peeraddr[2], sock.peeraddr[1], sock.gets())			
              broadcast_string(str, sock)
            end
          end
        end #for
      end
    end #while
  end #run

  private

  def broadcast_string(str, omit_sock)
    @descriptors.each do |clisock|
      if clisock != @serverSocket && clisock != omit_sock 
        clisock.write(str)
      end	
    end
    print(str)
  end #bo

  def accept_new_connection
    newsock = @serverSocket.accept
    @descriptors.push(newsock)
    newsock.write("You're connected to the Ruby chatserver\n")
    str = sprintf("Client joined %s:%s\n", 
                  newsock.peeraddr[2], newsock.peeraddr[1])
    broadcast_string(str, newsock)
  end

end #server

myChatServer = ChatServer.new('127.0.0.1', 2626)
myChatServer.run

