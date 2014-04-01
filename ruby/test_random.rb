class Dice
  attr_accessor :values
  def initialize
    # it is no neccessary to code here
  end

  def roll
    @values = Array.new  # neccessary
    5.times do 
      i = rand(5)
      @values << i 
      puts "#{i}"
    end
  end
end

dice = Dice.new
dice.roll
a = dice.values
dice.roll
b = dice.values
puts "#{a}, #{b}"

