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

tmp_no = 1
def test(tmp_no)
  print tmp_no.to_s 
  print "\n"
  tmp_no += 1
end

tmp_no = test(tmp_no)
tmp_no = test(tmp_no)


def test_ref(a)
  a += 1
end

ref_value=2
test_ref(ref_value)
print "#{ref_value}\n"
ref_value=test_ref(ref_value)
print "#{ref_value}\n"

or_value = "sdfsd"
#new_value 
new_value ||= or_value
print "#{new_value}\n"


