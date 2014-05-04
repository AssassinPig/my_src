var foo = {};
foo.attr_1 = 1;
foo.attr_2 = 2;
foo.fun = function() { console.log('hello world'); }

var foo = {
    prop : 'bar';
    fun : function() { 
      console.log('hello world'); 
    }
};

function User(name, uri) {
    this.name = name;
    this.uri = uri;
    this.display = function() { console.log('hello world'+this.name); }
}

var someone = new User('abc', 'http://www.xxx.com');
