require 'digest'
def gravatar_for(email, size=80)
  gravatar_id = Digest::MD5::hexdigest(email)
  gravatar_url = "https://secure.gravatar.com/avatar/#{gravatar_id}"
  #image_tag(gravatar_url, alt: "assassinpig", class: "gravatar")
end

email=ARGV[0]
print "#{gravatar_for(email)}\n"
