def full_title(page_title)
    base_title="Ruby On Rails Tutorial Sample App"
    if page_title.empty? 
        base_title
    else 
        "#{base_title} | #{page_title}"
    end
end

print full_title(""), "\n";
print full_title("abc"), "\n";

print File.expand_path(File.dirname(__FILE__))
print "\n"
print File.expand_path(".")
print "\n"
print File.dirname(__FILE__)
print "\n"

print 1.0e3
print "\n"
