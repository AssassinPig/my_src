require 'bcrypt'
include BCrypt

new_password="shao2014"
password_hash=Password.create(new_password)
puts password_hash
puts Password.new(password_hash)
if Password.new(password_hash) == new_password
  puts "give token"
end

salt = Array.new(10) { rand(1024).to_s(36) }.join
puts "#{salt}"

hashed_password = Digest::SHA256.hexdigest(salt+new_password)
puts "#{hashed_password}"

#puts hash(salt+new_password)
