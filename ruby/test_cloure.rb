def my_method
  x="Goodbye"
  yield("cruel")
end

x="hello"
my_method { |y| puts "#{x}, #{y} world" }
