#encoding: utf-8
require 'rubygems'
require 'mechanize'
require 'logger'

agent = Mechanize.new 
agent.log = Logger.new "fetch.log"
#agent.user_agent_alias = 'chrome'

todo_list = Array.new
visited_list = Array.new

#todo_list << "http://www.yhd.com/?tracker_u=1787&tracker_type=1&uid=73187445866"
todo_list << "http://www.china-pub.com/"
tmp_no = 1 

def save_page(page, tmp_no)
      #print "process link : #{page.title}\n"

      file_name = tmp_no.to_s 
      tmp_no += 1

      #print "save filename: #{file_name}\n"     
      html_file = File.join(File.expand_path(File.dirname(__FILE__) + "/web_fetched"), file_name) 

      #print "save path :#{html_file}\n" 

      File.open(html_file, "w+") do |file|
        file.puts page.body
      end
end

def right_url?(url)
    if url.class.to_s == "String" && ( url =~/\.(html|php|aspx|htm)/ || url.end_with?("/") )
      return true
    end

    false
end

while true
  print "========================\n"
  print "process #{todo_list.first}\n"
  page = agent.get todo_list.first 
  visited_list << todo_list.first
  todo_list.delete todo_list.first

  page.links.each do |link|
    if !visited_list.include?(link.href)
      print link.text, "\n"
      print link.href, "\n"

      if right_url?(link.href)
        todo_list << link.href
      end
    end
  end

  save_page(page, tmp_no)
  tmp_no += 1
  if todo_list.empty?
    break
  end
end

