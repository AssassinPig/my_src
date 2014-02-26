#encoding: utf-8
require "./crawler.rb"

x = Crawler.new
callback = lambda do |link|
    if link =~/\.(zip|rar|gz|pdf|doc)/
       x.remember(link)
       return Crawler::PASS
    elsif link =~/\.(jpg|jpeg)/
        return Crawler::DOWNLOAD
    end
    return Crawler::INDEX;
end

x.callback = callback
#x.start("http://www.zygames.com/")
#x.start("http://www.the9.com/")
x.start("http://www.srzc.com/")
