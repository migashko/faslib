class judge:
  def say(self):
    pass
  
class aspect_dredd:

  def one(self):
    print "one,",
    
  def two(self):
    print "two,",

  def three(self):
    print "three,",
      
  def strike(self):
    print "strike!"

  def say(self):
    self.one()
    self.two()
    self.three()
    self.strike()


class judge_dredd( aspect_dredd, judge):
  pass

# ----------------------------

class aspect_jon:
  def one(self):
    print "ONE,",

class judge_jon(aspect_jon, aspect_dredd, judge):
  pass

# ----------------------------

class aspect_bob:
  def three1(self):
    print "three and 0.5,",

  def three2(self):
    print "three and 0.75,",

  def three3(self):
    print "three and 0.99,",

  def three(self):
    print "three,",
    self.three1()
    self.three2()
    self.three3()

class judge_bob(aspect_bob, aspect_dredd, judge):
  pass

# ----------------------------

class aspect_sam(aspect_jon, aspect_bob):
  pass
  
class judge_sam(aspect_sam, aspect_dredd, judge):
  pass

# ----------------------------

dredd = judge_dredd()
print "Dredd:",
dredd.say()

jon = judge_jon()
print "Jon:",
jon.say()

bob = judge_bob()
print "Bob:",
bob.say()

sam = judge_sam()
print "Sam:",
sam.say()

