class MyClass

  def my_method(my_arg)
    my_arg*2
  end

  def public_fun
    private_fun
    #self.private_fun
    print self,"\n"
    print self.class, "\n"
  end

  private
  def private_fun
    puts "private_fun"
  end
end

obj=MyClass.new
obj.public_fun

print obj.my_method(3), "\n"
print obj.send(:my_method, 3), "\n"

class DataSource
  def get_cpu_info
  end
  def get_mem_info
  end
  def get_price_info
  end
  def get_x_info
  end
end

def define_component(name)
  print name, "\n"
end

ds=DataSource.new
#ds.methods.grep(/^get_(...)_info$/) { |m| print m, "\n" }
ds.methods.grep(/^get_(...)_info$/) { |m| define_component m  }


