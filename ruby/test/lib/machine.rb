class Machine 
  attr_accessor :states, :events
  attr_reader :state

  def initialize(states)
    @states = states
    @state = @states[0]
  end

  def trigger(event)
    @state = @events[event][:to] if @state= @events[event][:from]
  end

end
