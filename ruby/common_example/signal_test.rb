Signal.trap("INT") do 
  print "INT" 
  flag = true
end

flag = false
Thread.new do 
  while !flag 
    sleep(1000)
    print "thread sleep\n"
  end
  Process.exit()
end
