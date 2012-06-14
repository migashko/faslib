class dredd:

# ...

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

  def dredd_say(self):
    self.say()

# ----------------------------

class jon(dredd):

  # ...
  
  def one(self):
    print "ONE,",
  def jon_say(self):
    self.say()


# ----------------------------

class bob(dredd):

  # ...
  
  def four(self):
    print "four,",
  def five(self):
    print "five,",
  def six(self):
    print "six,",
  def seven(self):
    print "seven!"
  def say(self):
    self.one()
    self.two()
    self.three()
    self.four()
    self.five()
    self.six()
    self.seven()
  def bob_say(self):
    self.say()

# ----------------------------

class sam(bob, jon):
  
  # ...
  
  def one(self):
    jon.one(self)
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
