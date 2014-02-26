require 'girl'

describe 'Girl test' do
  subject { Girl.new }

  its(:chance?) { should be_true }

  it "taken!" do
    subject.taken!
    subject.should_not be_chance
  end
end
