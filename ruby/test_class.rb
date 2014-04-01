class Test
  def initialize(data)
    @data = data
  end

  def self.set_ms_data(data)
    @@msdata = data
  end

  def info
    print "#{@data}\n"
    print "#{@@msdata}\n"
  end

  def print_self
    print "#{self}\n"
  end

  def self.print_self
    print "#{self}\n"
  end

  def my_method
    @variable=1
  end
end

Test.set_ms_data(9)
t1=Test.new(1)
t1.info

Test.set_ms_data(8)
t2=Test.new(2)
t2.info

t2.print_self
Test.print_self

p t2.instance_variables
t2.my_method
p t2.instance_variables

print "\n"
p Test.instance_methods
p t2.methods
print "\n"

p Module.class
p Module.superclass
p Class.class
p Class.superclass

class Dog
  def bark
    "WOOF"
  end
end

class NewDog < Dog
  def gowl
    super.bark + ", ooo~"
  end
end

newDog = NewDog.new
newDog.gowl
