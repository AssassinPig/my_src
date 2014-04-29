require './utils.rb'

def get_word_info(line)
  lines = get_lines(line)
  word_num = 0
  lines.each do |line|
    word_num  += line.split(' ').length
  end

  word_num
end

print get_word_info(ARGV[0])
