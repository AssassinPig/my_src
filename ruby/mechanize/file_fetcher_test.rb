require 'rubygems'
require 'mechanize'

agent = Mechanize.new 
agent.user_agent_alias = 'Mac Safari'
#agent.auth("www.linuxidc.com", "www.linuxidc.com")

#page = agent.get('http://linux.linuxidc.com/2014%E5%B9%B4%E8%B5%84%E6%96%99/1%E6%9C%88/25%E6%97%A5/%E5%9B%BD%E5%86%85%E6%9C%80%E5%85%A8%E6%9C%80%E8%AF%A6%E7%BB%86%E7%9A%84Hadoop2.2.0%E9%9B%86%E7%BE%A4%E7%9A%84HA%E9%AB%98%E5%8F%AF%E9%9D%A0%E7%9A%84%E6%9C%80%E7%AE%80%E5%8D%95%E9%85%8D%E7%BD%AE/%E6%95%99%E7%A8%8B%E9%87%8D%E8%A6%81%E8%AF%B4%E6%98%8E.txt') 

page = agent.get('http://pic.dbmeizi.com/pics/by-all-means/s_p8834342.jpg') 

if page.class.to_s == "Mechanize::File" || page.class.to_s == "Mechanize::Image"
  puts page.class 
  page.save("temp.jpg")
end
