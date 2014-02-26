require 'machine.rb'

describe Machine do
  before :each do
    @machine = Machine.new([:shopping, :checking_out])
    @machine.events = { :checkout =>
                  {:from => :shopping, :to => :checking_out},
                  :accept_card => {:from => :checking_out, :to => :success} }
  end

  it "should initilally have a state of :initial" do
    @machine.state.should == :shopping 
  end

  it "should remember a list fo valid states" do
    @machine.states.should == [:shopping, :checking_out]
  end

  it "should remember a list of events with transitions" do
    @machine.events.should == { :checkout =>
                  {:from => :shopping, :to => :checking_out},
                  :accept_card => {:from => :checking_out, :to => :success} }
  end
  
  it "should transition to :checking_out upon #trigger(:checking_out) event" do
    @machine.trigger(:checkout)
    @machine.state.should == :checking_out 
  end

  it "should transition to :success upon#trigger(:accept_card)" do
    @machine.events = { :checkout => { :from => :shopping, :to => :checking_out}, :accept_card => { :from => :checking_out, :to => :success } }  

    @machine.trigger(:checkout)
    @machine.state.should == :checking_out
    @machine.trigger(:accept_card)
    @machine.state.should == :success
  end
end
