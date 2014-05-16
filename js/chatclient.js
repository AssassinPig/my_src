var net = require('net');
var util= require('util');
var readline = require('readline');

var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.setPrompt('input>');
rl.prompt();

var client = net.createConnection(8124, '127.0.0.1', function(s){
  console.log('connect ok');
});

rl.on('line', function(line){
  if(line == "quit")
  {
    console.log("quit");
    client.end(line, 'utf8', function(){
    });
  } else {
    client.write(line, 'utf8', function(){
    });
  }
});

client.on('end', function(){
  console.log('server disconnected');
  rl.close();
});

client.on('error', function(){
  console.log('server error');
  rl.close();
});

client.on('data', function(string){
  console.log('recv :'+string);
});

rl.on('close', function(){
  //client.end();
  console.log("close");
  process.exit(0);
});
