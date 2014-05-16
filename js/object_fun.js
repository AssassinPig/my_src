function User(name, email) {
  this.name = name;
  this.email = email;
  this.fun = function() {
    console.log("fun");
  }
}

User.prototype.save = function() {
  console.log("user save function");
}

User.get = function() {
  console.log("get function");
}

user = new User('abc', 'de@gmail.com');

user.save();
user.fun();
//user.get();
User.get();
