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


class dredd:
  def dredd_say(self):
    self.say()

dredd.one = say_one
dredd.two = say_two
dredd.three = say_three
dredd.strike = say_strike
dredd.say = say_123s

# ----------------------------

def say_ONE(self):
  print "ONE,",

class jon:
  def jon_say(self):
    self.say()

jon.one = say_ONE
jon.two = say_two
jon.three = say_three
jon.strike = say_strike
jon.say = say_123s


# ----------------------------

def say_four(self):
  print "four,",
  
def say_five(self):
  print "five,",
  
def say_six(self):
  print "six,",
  
def say_seven(self):
  print "seven!"

def say_1234567(self):
  self.one()
  self.two()
  self.three()
  self.four()
  self.five()
  self.six()
  self.seven()



class bob(dredd):
  def bob_say(self):
    self.say()

bob.one = say_one
bob.two = say_two
bob.three = say_three
bob.four = say_four
bob.five = say_five
bob.six = say_six
bob.seven = say_seven
bob.say = say_1234567

# ----------------------------

class sam:
  def sam_say(self):
    self.say()

sam.one = say_ONE
sam.two = say_two
sam.three = say_three
sam.four = say_four
sam.five = say_five
sam.six = say_six
sam.seven = say_seven
sam.say = say_1234567

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
