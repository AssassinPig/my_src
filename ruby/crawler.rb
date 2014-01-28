#encoding: utf-8
require "rubygems"
require "mechanize"

class Crawler < Mechanize

    attr_accessor :callback
    INDEX = 0
    DOWNLOAD = 1
    PASS = 2

    def initialize
        super
        init
        @first = true
        #self.user_agent_alias = "Windows IE 6"
    end

    def init
        @visited = []
    end

    def remember(link)
        @visited << link
    end

    def perform_index(link)
        self.get(link)
        if(self.page.class.to_s == "Mechanize::Page")
            links = self.page.links.map {|link| link.href } - @visited
            links.each do |alink|
                start(alink)
            end
        end
    end

    def start(link)
        return if link.nil?
        if(!@visited.include?(link))
            action = @callback.call(link)
            if(@first)
                @first = false
                perform_index(link)
            end
            case action
            when INDEX
                puts "======================"
                puts "link #{link} save as:"
                #puts File.basename(link)
                puts "======================"
                #self.get(link).save_as(File.basename(link))
                perform_index(link)
            when DOWNLOAD
                #self.get(link).save_as(File.basename(link))
            when PASS
                puts "passing on #{link}"
            end
        end
    end

    def get(site)
        begin
            puts "getting #{site}"
            @visited << site
            super(site)
        rescue
            puts "error getting #{site}"
        end
    end
end
