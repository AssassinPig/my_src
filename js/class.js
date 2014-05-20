var Person = function(firstName, lastName, age) {
  this.firstName = firstName;
  this.lastName = lastName;
  this.age = age;
}

Person.prototype.fullName = function(){
  return this.firstName + " " + this.lastName;
};

var Spy = function(firstName, lastName, age){
  this.firstName = firstName;
  this.lastName = lastName;
  this.age = age;
};

Spy.prototype = new Person();           //注意这里
Spy.prototype.spy = function(){
  console.log('spy age:' + this.age);
}

var person = new Person('json', 'borne', 30);
console.log(person.fullName());

var mySpy = new Spy('firstName', 'lastName', 29);
console.log(mySpy.fullName());
mySpy.spy();
