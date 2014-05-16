var v1='v1';

var f1 = function() {
  console.log(v1);
}

f1();

var scope = 'global';
var f = function() {
  console.log(scope);
  var scope = 'f';
}
f();

