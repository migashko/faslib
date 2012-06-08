class judge_dredd:
  
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

# ----------------------------

class judge_jon(judge_dredd):
  pass

def say_ONE(self):
  print "ONE,",

judge_jon.one = say_ONE

# ----------------------------

class judge_bob(judge_dredd):
  pass

def say_three1(self):
  print "three and 0.5,",

def say_three2(self):
  print "three and 0.75,",

def say_three3(self):
  print "three and 0.99,",

def say_three(self):
  print "three,",
  self.three1()
  self.three2()
  self.three3()

judge_bob.three = say_three
judge_bob.three1 = say_three1
judge_bob.three2 = say_three2
judge_bob.three3 = say_three3

# ----------------------------

class judge_sam(judge_dredd):
  pass

judge_sam.one = say_ONE
judge_sam.three = say_three
judge_sam.three1 = say_three1
judge_sam.three2 = say_three2
judge_sam.three3 = say_three3

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

