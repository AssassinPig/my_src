t = Thread.new do
  puts "in thread"
end

#t.join
puts "out thread"
t.join
