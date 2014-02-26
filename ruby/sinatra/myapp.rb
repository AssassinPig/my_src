require 'sinatra'

get '/' do
  #code = "<%= Time.now %>"
  erb :index 
end

configure do
  set :bind=>'192.168.0.120'
  set :port=>4567
end
