Useful links:
http://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/#for-end-users-that-dont-need-to-commit-or-do-any-development
https://wiki.physik.uzh.ch/cms/limits:limits

 ## How to run and install: 
For installing Combine follow procedures in:

https://cms-hcomb.gitbook.io/combine/setting-up-the-analysis

after the first installation you can instead just do:

cd CMSSW_10_2_13/src/HiggsAnalysis/CombinedLimit
cmsenv

a really fast (but not updated guide, can be found here https://wiki.physik.uzh.ch/cms/limits:limits)

A good example of datacard can be found here: https://twiki.cern.ch/twiki/bin/view/Sandbox/LPCStatsHandsOnTutorial
for Asymptotic method (deafult one, also used in HCMN Run 2 previous search) the command is:

combine -M AsymptoticLimits -S 0 ExampleDatacard/L12000_M500.txt #-S 0 doesn't consider systematic uncertainties

The output is the limit on the signal strenght r=(\sigma*BR)_obs / (\sigma*BR)_theory
(for a formal definition of signal strenght see ATLAS paper: https://arxiv.org/pdf/1507.04548.pdf)

In case you are running without observed data the procedure is described in the HN: https://hypernews.cern.ch/HyperNews/CMS/get/higgs-combination/914/1/1.html so you need a dummy histogram with whatever bin content you want and call it "data_obs" and put it in the file. Then you should use "--run blind", like in the following example:

<combine -M AsymptoticLimits -S 0 L5_M5000.txt  --run blind>



