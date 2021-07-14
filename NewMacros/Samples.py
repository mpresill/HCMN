from EventLoop import EventLoop

# here we define a class per sample we want to run on
# testing on 2016 
# -----------------------------------
class SampleL13M1000ele(EventLoop):
 """ event loop over the gluon-gluon fusion sample
 """ 
 def __init__(self):
  # call the inherited constructor
  EventLoop.__init__(self, "eejj_L13_M1000")

  # add the eejj_L13_M1000 samples into the event loop
  self.eventLoop.inputFiles.push_back('/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_HOPE/eejj_L13_M1000_2016.root')


# -----------------------------------
class SampleTTtW(EventLoop):
 """ event loop over the vector boson fusion sample
 """ 
 def __init__(self):
  # call the inherited constructor
  EventLoop.__init__(self, "TTtW")

  # add the TTtW samples into the event loop
  self.eventLoop.inputFiles.push_back('/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_HOPE/TTtW_2016.root')