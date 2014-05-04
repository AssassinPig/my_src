function Output(name) {
  this.name = name;
  this.fun = function() {
    console.log("output name:"+this.name); 
  }
}

Output.fun1 = function() {
  console.log('fun1 here');
}

Output.prototype.fun2 = function() {
  console.log('fun2 here');
}

module.exports = Output;
