from Algorithm import Algorithm
from ROOT import TH1D

#here we create two classes of histograms with different binning 
# -----------------------------------
class AlgDefault(Algorithm):
 """ Default set of histograms
 """
 def __init__(self):
  # call inherited constructor
  Algorithm.__init__(self, "AlgDefault")

  # create histograms
  self.alg.h_pt_e1 = TH1D("h_pt_e1", ";#it{p}_{T} (e_{1}) [GeV];Events", 30, 0, 300)

# -----------------------------------
class AlgFineBinning(Algorithm):
 """ set of histograms with fine binning
 """
 def __init__(self):
  # call inherited constructor
  Algorithm.__init__(self, "AlgFineBinning")

  # create histograms: fine binning
  self.alg.h_pt_e1 = TH1D("h_pt_e1", ";#it{p}_{T} (e_{1}) [GeV];Events", 300, 0, 300)
