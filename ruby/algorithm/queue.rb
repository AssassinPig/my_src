class Queue
  def initialize
    @items = []
  end

  def push(elem)
    @items.insert 0, elem
  end

  def pop
    @items.pop
  end

  #alias :<< :elem

  def empty?
    @items.empty?
  end

  def size
    @items.size
  end

  def display
    @items.each do |i| 
      print "#{i}"
    end
    print "\n"
  end
end

queue = Queue.new
for i in 1..5 do 
  queue.push i
end
queue.display

2.times do 
  queue.pop
end
queue.display
