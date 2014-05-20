var net = require('net');
var util = require('util');
var http = require('http');
var dns = require('dns');
var events = require('events');
var EventsEmitter = require('events').EventEmitter;
var events_emitter = new EventsEmitter(); 

//var url = 'nodejs.org/api/dns.html';
//var url = 'www.baidu.com';
var url = 'nodejs.org';

function myResolve(url, callback){
  dns.resolve4(url, function(err, address){
    if(err) {
      console.log("url resolve failed"); 
    } else {
      console.log("url resolve success: "+address); 
      //callback(address);
      events_emitter.emit('myResolve', address);   
    }
  });
}

function myGetCallback(address){
  console.log("resolved address: " + address);
  //var client = http.createClient(80, ''); 
}

//myResolve(url, myGetCallback);
events_emitter.on('myResolve', function(address){
  myGetCallback(address);
});

//module.exports = myResolve;

//var myResolver = function(){} 
//myResolve.prototype.myResolve = function(url, callback){}
//module.exports = myResolver;

