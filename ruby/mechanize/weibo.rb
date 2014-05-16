#encoding: utf-8
require 'rubygems'
require 'mechanize'
require 'logger'

agent = Mechanize.new 
agent.user_agent_alias = 'Mac Safari'
system("rm fetch.log")
agent.log = Logger.new "fetch.log"

todo_list = Array.new
visited_list = Array.new

todo_list << "http://tieba.baidu.com/"
page = agent.get todo_list.first 

page.forms.each do |form| 
  form.fields.each do |field|
    puts field.name
  end
end
#puts page.body
#puts page.forms.first
