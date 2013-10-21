var net = require('net');
var util= require('util');

var clients = new Array;
var server = net.createServer(function(c){
	//console.log('client '+util.inspect(c.address())+'has connected');
	//console.log('client has connected');
});
	
server.listen(8124, function(){
	console.log('server bound');
});

server.on('connection', function(c){
	console.log('client connect');		
	clients.push(c);

	c.on('end', function(){
		console.log('server disconnected');
		
		for(var i=0; i<clients.length; ++i)
		{
			if(c == clients[i])
			{
				c.end();
				console.log('remove client 0');
				clients.splice(i, 1);
				break;
			}
		}
	});
	
	c.on('error', function(e){
		console.log('error occurs');
		console.log(e.code);
		
		for(var i=0; i<clients.length; ++i)
		{
			if(c == clients[i])
			{
				//c.end();
				console.log('remove client 2');
				clients.splice(i, 1);
				break;
			}
		}
	});
	
	c.on('data', function(string){
		console.log('recv from '+util.inspect(c.remoteAddress)+"["+c.remotePort+"] : " +string);
		for(var i=0; i<clients.length; ++i)
		{
			var client = clients[i];
			client.write(string, 'utf8', function(){
				if(string == 'quit')
				{
					console.log('client quit');
					//client.end();
					
					for(var i=0; i<clients.length; ++i)
					{
						if(client == clients[i])
						{
							//client.end();
							console.log('remove client 1');
							clients.splice(i, 1);
							return;
						}
					}
				}
			});
		}
	});
});
