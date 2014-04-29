require './utils.rb'
def format_lines(lines)
  lines.each_with_index do |l, i|
    print "#{i+1}: #{l}"
  end

  print "total: #{lines.size}\n"
end

def get_code_info(file)
  print "#{file}\n"
  lines = get_lines(file);
  format_lines(lines);
end

get_code_info(ARGV[0])
