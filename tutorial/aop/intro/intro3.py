class judge:
  def say(self):
    pass

def say_one(self):
  print "one,",
    
def say_two(self):
  print "two,",

def say_three(self):
  print "three,",
      
def say_strike(self):
  print "strike!"

def say_say(self):
  self.one()
  self.two()
  self.three()
  self.strike()

class aspect_dredd:
  pass

aspect_dredd.one = say_one
aspect_dredd.two = say_two
aspect_dredd.three = say_three
aspect_dredd.strike = say_strike
aspect_dredd.say = say_say


class judge_dredd( aspect_dredd, judge):
  pass

# ----------------------------

class aspect_jon:
  pass

def say_ONE(self):
    print "ONE,",
    
aspect_jon.one = say_ONE

class judge_jon(aspect_jon, aspect_dredd, judge):
  pass

# ----------------------------

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

class aspect_bob:
  pass 

aspect_bob.three = say_three
aspect_bob.three1 = say_three1
aspect_bob.three2 = say_three2
aspect_bob.three3 = say_three3

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

