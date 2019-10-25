import json
import ROOT
import numpy as np

with open("RunBCDEF_SF_TRIG.json") as f1:
    test = json.load(f1)

with open("RunGH_SF_TRIG.json") as f2:
    test2 = json.load(f2)

print ("pt_low;pt_high;eta_low;eta_high;value;stat;syst")
for key, value in test["Mu50_OR_TkMu50_PtEtaBins"]["pt_abseta_ratio"].items():

    pt = key.split(":")[1]
    pt_low = pt.split("[")[1].split(',')[0]
    pt_high = pt.split("]")[0].split(',')[1]

    print("if(pt>%s && pt<=%s){" % (pt_low, pt_high))
    
    
    
    for eta_int, dic in value.items():

        dic2 = test2["Mu50_OR_TkMu50_PtEtaBins"]["pt_abseta_ratio"][key][eta_int]

        eta = eta_int.split(":")[1]
        eta_low = eta.split("[")[1].split(",")[0]
        eta_high = eta.split("]")[0].split(",")[1]

        value = (dic["value"]*35.89+dic2["value"]*32.58)/68.47
        error = (dic["error"]*35.89+dic2["error"]*32.58)/68.47
       # syst = (dic["syst"]*35.89+dic2["syst"]*32.58)/68.47

        print("    if(eta > %s && eta <= %s) musf=%s; // error %s " % (eta_low, eta_high, value, error))

    print("}")
