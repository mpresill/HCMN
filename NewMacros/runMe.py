# here we load the shared library created using the Makefile
from ROOT import gSystem
gSystem.Load("Analysis.so")

# now we can create instance of the class EventLoop
from ROOT import EventLoop
eventLoop = EventLoop()

# set the attributes. All public attributes are accessible

# 1. name of the tree. In this example, we use HCMN analysis, where
# tree is called BOOM
eventLoop.treeName = "BOOM"

# 2. add the input files. We use MC simulation of some process
# If the data are stored in multiple files we have to declare multiple times the following line
eventLoop.inputFiles.push_back('/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_HOPE/eejj_L13_M1000_2016.root')
#eventLoop.inputFiles.push_back('/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_HOPE') #if they are stored in multiple files uncomment here



# create algorithm(s)
from ROOT import Algorithm
alg = Algorithm()

# create the histograms
from ROOT import TH1D
alg.h_pt_e1 = TH1D("h_pt_e1", ";#it{p}_{T} (e_{1}) [GeV];Events", 30, 0, 300)
alg.h_pt_e1.Sumw2()

# add the algorithm into the event loop
eventLoop.algorithms.push_back( alg )



# initialize and execute the event loop
eventLoop.initialize()
eventLoop.execute()



# Create a new ROOT file
from ROOT import TFile
f = TFile.Open("histograms.root", "recreate")
f.cd()

# save the histogram
alg.h_pt_e1.Write()

# close the file
f.Close()