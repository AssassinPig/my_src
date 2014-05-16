(function(){
  console.log('call fun');
}).call();

var refObj = {}
console.log(refObj);

(function(){
  this.abc = 'abc';
}).call(refObj);

console.log(refObj);
