def my_method(*args)
  args.map { |arg| arg.reverse }
end

def my_method2(args)
  args.map { |arg| arg.reverse }
end

a = [ 'abc', 'xyz', '123' ]
puts my_method(a)
puts a

puts my_method2(a)
puts a
