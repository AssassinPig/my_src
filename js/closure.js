var closure = function() {
  var count = 0;
  var get = function() {
    count++; 
    return count;
  }
  return get;
}

var counter1 = closure();
var counter2 = closure();
console.log(counter1());
console.log(counter2());
console.log(counter1());
console.log(counter2());

