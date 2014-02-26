v1=1
class MyClass
  v2=2
  print "2 #{local_variables}\n"
  def myFun
    v3 = 1
    print "3 #{local_variables}\n"
  end
  print "2 #{local_variables}\n"
end

print "1 #{local_variables}\n"
myClass=MyClass.new
myClass.myFun
myClass.myFun
print "1 #{local_variables}\n"
