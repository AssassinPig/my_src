var fs = require('fs');
fs.readFile('scope.js', 'utf-8', function(err, data){
  if(err) {
    console.log(err); 
  } else {
    console.log(data); 
  }
});

fs.writeFile('message.txt', 'Hello Node', function (err) {
  if (err) throw err;
  console.log('It\'s saved!');
});