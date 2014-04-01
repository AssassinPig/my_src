class MyClass
  def self.my_method_1
  end
end

def MyClass.my_method_3
end

obj=MyClass.new
def obj.my_method_2
end

MyClass.my_method_1

#obj.my_method_1
obj.my_method_2
#obj.my_method_3
MyClass.my_method_3

obj2=MyClass.new
#obj2.my_method_1
#obj2.my_method_2
#obj2.my_method_3
