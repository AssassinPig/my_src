def call_back
    yield
    yield
end

def call_back
    yield 1
    yield 2
end

call_back { puts "in block" }
call_back { |a| print "#{a}\n"} 
