class Test
    def initialize(data)
        @data = data
    end

    def self.set_ms_data(data)
        @@msdata = data
    end

    def info
        print "#{@data}\n"
        print "#{@@msdata}\n"
    end
end

Test.set_ms_data(9)
t1=Test.new(1)
t1.info

Test.set_ms_data(8)
t2=Test.new(2)
t2.info

