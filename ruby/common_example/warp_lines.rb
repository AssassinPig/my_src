require './utils.rb'
def get_warp_info(file)
  lines = get_lines(file)

  lines.inject('') do |output, line|
    output += softwarp_line(line)
  end.gsub(/\t+/, ' ').gsub(/ +/, ' ')
end

def softwarp_line(line)
  return "\n\n" if line == "\n"
  return line.chomp + ' '
end

get_warp_info(ARGV[0])
