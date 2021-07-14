from ROOT import EventLoop as EventLoopCpp

class EventLoop(object):
 """ Wrapper around the c++ class event loop
 """ 
 def __init__(self, name):
  # set the event loop name
  self.name = name

  # now we can create instance of the c++ class EventLoop
  self.eventLoop = EventLoopCpp()

  # set the tree name attribute
  self.eventLoop.treeName = "BOOM"

  # keep the list of python Algorithm class instances
  self.algs = []

 def addAlgorithm(self, algorithm):
  """ add an algorithm into this event loop
  """
  algorithm.setSumw2()
  self.algs += [ algorithm ]
  self.eventLoop.algorithms.push_back(algorithm.alg)
 
 def addAlgorithms(self, algorithms):
  """ add multiple algorithms into this event loop
  """
  for alg in algorithms:
   self.addAlgorithm(alg)

 def execute(self):
  """ initialize and execute the event loop
  """
  self.eventLoop.initialize()
  self.eventLoop.execute()

 def save(self):
  """ save histograms from all algorithms
  """
  for alg in self.algs:
   alg.save(self.name)