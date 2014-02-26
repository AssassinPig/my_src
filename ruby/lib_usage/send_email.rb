require 'rubygems'
require 'mail'
mail=Mail.new do
    from    'assassinpig@gmail.com'
    to      'zhufengShao2011@gmail.com'
    subject 'Here is the image you wanted'
    body    File.read('body.txt')
    add_file 'body.txt'
end

mail.deliver
