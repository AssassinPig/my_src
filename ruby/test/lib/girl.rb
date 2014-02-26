class Girl
  attr_accessor :taken
  def chance?
    !taken
  end

  def taken?
      !chance? 
  end

  def taken!
      self.taken = true
  end

end
