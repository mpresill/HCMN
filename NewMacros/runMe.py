# here we load the shared library created using the Makefile
from ROOT import gSystem
gSystem.Load("Analysis.so")

# now we can create instance of the class EventLoop
from Samples import *
eventLoop = SampleL13M1000ele()

# create algorithm
from Algorithms import * 
algs = []
algs += [ AlgDefault() ]
algs += [ AlgFineBinning() ]

# add the algorithm into the event loop
eventLoop.addAlgorithms( algs )

# initialize and execute the event loop
eventLoop.execute()

# save plots from all algorithms in the loop
eventLoop.save()