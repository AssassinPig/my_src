print File.expand_path(File.dirname(__FILE__))
print "\n"
print File.expand_path(".")
print "\n"
print File.dirname(__FILE__)
print "\n"

print 1.0e3
print "\n"

class MyClass
  def myFun
    @v=1 
  end

  private
  def myPrivateFun
  end
end

obj1=MyClass.new
obj1.myFun
obj2=MyClass.new
print "#{obj1.instance_variables}\n"
print "#{obj2.instance_variables}\n"
print "#{MyClass.ancestors}\n"

class MyChildClass < MyClass
  def myPublicFun
    myPrivateFun
  end
end

childObj=MyChildClass.new
childObj.myPublicFun

print "#{$0}\n"
print "#{__FILE__}\n"

a = 'c'
if a == 'a'
  puts 'a'
elsif a == 'b' 
  puts 'b'
else
  puts 'other'
end

a = "1,2,3,4"
b = []
a.split(',').each do |i|
  b << i.to_i
end
print b

def make_array(*args)
  print args
  print "\n"
end
make_array('a','b','c')

class StaticModule
  def self.call
    print "StaticModule.call\n"
  end
end

StaticModule.call
