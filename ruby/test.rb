def full_title(page_title)
    base_title="Ruby On Rails Tutorial Sample App"
    if page_title.empty? 
        base_title
    else 
        "#{base_title} | #{page_title}"
    end
end

print full_title(""), "\n";
print full_title("abc"), "\n";

print File.expand_path(File.dirname(__FILE__))
print "\n"
print File.expand_path(".")
print "\n"
print File.dirname(__FILE__)
print "\n"

print 1.0e3
print "\n"

tmp_no = 1
def test(tmp_no)
  print tmp_no.to_s 
  print "\n"
  tmp_no += 1
end

tmp_no = test(tmp_no)
tmp_no = test(tmp_no)


def test_ref(a)
  a += 1
end

ref_value=2
test_ref(ref_value)
print "#{ref_value}\n"
ref_value=test_ref(ref_value)
print "#{ref_value}\n"

or_value = "sdfsd"
#new_value 
new_value ||= or_value
print "#{new_value}\n"

def test_array_ref(a)
  #a.reverse #no
  #a=a.reverse #no
  #a.reverse  #no
  a.reverse! #yes
end
a=[1,2,3]
print "before #{a}\n"
print "return #{test_array_ref(a)}\n"
print "after #{a}\n"


class MyClass
  def myFun
    @v=1 
  end

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
