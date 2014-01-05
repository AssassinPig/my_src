def call_c():
  c_module = loadmodule("./test.so") 
  print c_module.my_c_function("yes")
  print c_module.my_c_function("no")
  print c_module.my_c_function("other")

if __name__ == '__main__':
  call_c()
