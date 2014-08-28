var crypto = require('crypto');
var shasum =  crypto.createHash('sha1');

var encrypt = {
	name : 'assassinpig',
    email : 'assassinpig@gmail.com',
    password : '123456'
};

//console.log(encrypt);
for(var k in encrypt) {
	//console.log(k);
	//console.log(encrypt[k]);
	shasum.update(encrypt[k]);
}

var content = shasum.digest('hex');
console.log('encrypt content: '+content);