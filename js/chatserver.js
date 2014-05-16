var net = require('net');
var util= require('util');

var clients = new Array;
var server = net.createServer(function(c){
  //console.log('client '+util.inspect(c.address())+'has connected');
  //console.log('client has connected');
});

function removeClients(connect) {
    for(var i=0; i<clients.length; ++i) {
      if(connect == clients[i]) {
        connect.end();
        clients.splice(i, 1);
        break;
      }
    }
}

function broadcast(data) {
    for(var i=0; i<clients.length; ++i) {
      var client = clients[i];
      client.write(data, 'utf8', function(){
        if(data == 'quit') {
          console.log('client quit');
        }
      });
    }
}

server.listen(8124, function(){
  console.log('server bound');
});

server.on('connection', function(c){
  console.log('client connect');		
  clients.push(c);

  c.on('end', function(){
    console.log('server disconnected');
    removeClients(this);
  });

  c.on('error', function(e){
    console.log('error occurs');
    console.log(e.code);
    removeClients(this);
  });

  c.on('data', function(data){
    console.log('recv from '+util.inspect(c.remoteAddress)+"["+c.remotePort+"] : " + data);
    broadcast(data);
  });
});
