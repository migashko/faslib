class helloworld:
    def hello(self):
        print "hello",

    def world(self):
        print "world"

    def say(self):
        self.hello()
        self.world()

def World(self):
  print "World"

helloworld.world = World
h = helloworld()
h.say()