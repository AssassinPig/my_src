#encoding: utf-8
require 'rubygems'
require 'mechanize'
require 'logger'

agent = Mechanize.new 
agent.user_agent_alias = 'Mac Safari'
#agent.auth("www.linuxidc.com", "www.linuxidc.com") 
system("rm fetch.log")
agent.log = Logger.new "fetch.log"

todo_list = Array.new
visited_list = Array.new

#todo_list << "http://linux.linuxidc.com/"
todo_list << "http://www.mynvshen.com/12002/top"

def save_page(page, tmp_no)
      #print "process link : #{page.title}\n"
      file_name  

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
  begin
    page = agent.get todo_list.first 
  rescue Mechanize::ResponseCodeError => e
    todo_list.delete todo_list.first
    next
  rescue Mechanize::ResponseReadError => e
    todo_list.delete todo_list.first
    next
  end

  visited_list << todo_list.first
  current_page_href = todo_list.delete todo_list.first

  page.images.each do |image|
    puts "image.save #{image.url}"
    image_agent = Mechanize.new
    image_agent.user_agent_alias = 'Mac Safari'
    image_page = image_agent.get(image.url)
    if image_page.class.to_s == "Mechanize::File" || image_page.class.to_s == "Mechanize::Image"
      filename = image.url.to_s.split('/').last 

      image_file = File.join(File.expand_path(File.dirname(__FILE__) + "/web_fetched"), filename) 
      puts "save as: #{image_file}"
      image_page.save(image_file)
    end
  end

  page.links.each do |link|
    link_href_s = link.href.to_s

    puts "link:"
    puts "current_page_href: #{current_page_href}"
    puts "link_href_s: #{link_href_s}"

    if !link_href_s.start_with?('http')
      if link_href_s.start_with?('/')
        link_href_s.slice!(0)
      end

      if current_page_href.end_with?('/')
        link_href_s = current_page_href + link_href_s 
        puts "link_href_s: #{link_href_s}"
      end
    end

    if !visited_list.include?(link_href_s)
      #if right_url?(link.href) && link.href.to_s.include?('dbmeizi')
      if link_href_s.include?('mynvshen')
        todo_list << link_href_s 
      end

    end
  end

  #save_page(page, tmp_no)
  if todo_list.empty?
    break
  end
end

