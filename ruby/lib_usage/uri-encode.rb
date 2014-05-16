require 'uri'

#enc_uri = URI.escape()
#p enc_uri

p URI.unescape('http://weibo.com/login.php?url=http%3A%2F%2Fweibo.com%2Fguide%2Fwelcome&from=weiyonghulogin')

p URI.unescape('http://weibo.com/login.php?url=http%3A%2F%2Fweibo.com%2Flogin.php%3Furl%3Dhttp%253A%252F%252Fweibo.com%252Fguide%252Fwelcome%26from%3Dweiyonghulogin')

p URI.unescape('http%3A%2F%2Fweibo.com%2Fguide%2Fwelcome')
