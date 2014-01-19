require 'mysql2'
client = Mysql2::Client.new(:host => "192.168.0.120", :username => "zhufeng",:password=>"654321",:database=>"myblog")
results = client.query("select * from users");
results.each do |hash|
      puts hash.map { |k,v| "#{k} = #{v}" }.join(", ")
end
