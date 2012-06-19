
def say_one(self):
  print "one,",
    
def say_two(self):
  print "two,",

def say_three(self):
  print "three,",
      
def say_strike(self):
  print "strike!"

def say_123s(self):
  self.one()
  self.two()
  self.three()
  self.strike()

class aspect_123s:
  pass

aspect_123s.one = say_one
aspect_123s.two = say_two
aspect_123s.three = say_three
aspect_123s.strike = say_strike
aspect_123s.say = say_123s

# ----------------------------

class dredd( aspect_123s ):
# ...
  def dredd_say(self):
    self.say()

# ----------------------------

class aspect_ONE:
  pass

def say_ONE(self):
    print "ONE,",
    
aspect_ONE.one = say_ONE

# ----------------------------

class jon(aspect_ONE, aspect_123s):
# ...
  def jon_say(self):
    self.say()

# ----------------------------

def say_four(self):
  print "four,",

def say_five(self):
  print "five,",

def say_six(self):
  print "six,",

def say_seven(self):
  print "seven!"

def say_123567(self):
  self.say_123()
  self.four()
  self.five()
  self.six()
  self.seven()

def stub(self):
  pass

class aspect_1234567(aspect_123s):
  pass

aspect_1234567.strike = stub
aspect_1234567.four = say_four
aspect_1234567.five = say_five
aspect_1234567.six = say_six
aspect_1234567.seven = say_seven
aspect_1234567.say_123 = aspect_1234567.say
aspect_1234567.say = say_123567

# ----------------------------

class bob(aspect_1234567):
# ...
  def bob_say(self):
    self.say()

# ----------------------------

class aspect_ONE234567(aspect_ONE, aspect_1234567):
  pass
  
class sam(aspect_ONE234567):
# ...
  def sam_say(self):
    self.say()


# ----------------------------

d = dredd()
print "Dredd:",
d.dredd_say()

j = jon()
print "Jon:",
j.jon_say()

b = bob()
print "Bob:",
b.bob_say()

s = sam()
print "Sam:",
s.sam_say()
