var mongoose = require('mongoose');


/*
var db = mongoose.createConnection('localhost', 'test');
db.on('error', console.error.bind(console, 'connection failed'));
db.once('open', function(){
	console.log('open database success');
	callback();
});
*/
var config = {
	db: 'mongodb://127.0.0.1/zshop'
};

var db = mongoose.connect(config.db, function (err) {
  if (err) {
    console.error('connect to %s error: ', config.db, err.message);
    process.exit(1);
  }
  callback();
});

function callback() {
	//定义schema
	var PersonSchema = new mongoose.Schema({
		name: String,
		email: String
	});

	//定义model
	var PersonModel = db.model('Person', PersonSchema);
	//var personModel = db.model('Person');

	//定义entity
	//var personEntity = new PersonModel({name:'Krouky', email:'abcdef@mail.com'});
	//console.log(personEntity.name);

	//Entity有CURD方法
	//personEntity.save();

	//执行查询使用model，entity也可以做到
	PersonModel.findOne({name:'Krouky'}, function(err, person){
		if(err) {
			console.log('no match data');
			return;
		}
		console.log(person);
			
		
		PersonModel.update({name: 'new name'}, person, function(err){
			if(err) {
				console.log('update failed:'+err);
			} else {
				console.log('update success');
			}
		});
		
		//person.remove();
	});
	
	/*//查找所有
	PersonModel.find(function(err, persons){
		if(err) {
			console.log('no match data');
			return;
		}

		
		for(var i=0; i<persons.length; ++i) {
			//console.log(persons[i]);
			var p = persons[i];
			p.remove();
		}
	});
	*/
}

