#!/bin/bash
# to find sample path in Legnaro:
# xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill
rm listST.txt;
rm listZZ.txt;
rm listWZ.txt;
rm listWW.txt;
rm listWJets.txt;
rm listDY.txt;
rm listTT.txt;

rm list_eejjL13M500.txt;
rm list_eejjL13M1000.txt;
rm list_eejjL13M2000.txt;
rm list_eejjL13M5000.txt;
rm list_eejjL13M8000.txt;
rm list_mumujjL13M500.txt;
rm list_mumujjL13M1000.txt;
rm list_mumujjL13M2000.txt;
rm list_mumujjL13M5000.txt;
rm list_mumujjL13M8000.txt;

rm list_single_ele_B.txt;
rm list_single_ele_C.txt;
rm list_single_ele_D.txt;
rm list_single_ele_E.txt;
rm list_single_ele_F.txt;

rm list_single_mu_B.txt
rm list_single_mu_C.txt
rm list_single_mu_D.txt
rm list_single_mu_E.txt
rm list_single_mu_F.txt

#DY
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_DY1/191023_102411/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listDY.txt done

for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_DY2/191023_102649/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listDY.txt done

sed -i -e "s/\"/\\\\\"/g" listDY.txt
sed -i -e "s/\//\\\\\//g" listDY.txt

#TT
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/Fall17V2_TT/191022_133904/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listTT.txt; done

for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/Fall17V2_TT/191023_094710/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listTT.txt; done

sed -i -e "s/\"/\\\\\"/g" listTT.txt
sed -i -e "s/\//\\\\\//g" listTT.txt

#ST
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/Fall17V2_SaT/191023_095224/0000`;        
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listST.txt; done

for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/Fall17V2_ST/191023_094957/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listST.txt; done

sed -i -e "s/\"/\\\\\"/g" listST.txt
sed -i -e "s/\//\\\\\//g" listST.txt

#ZZ
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/ZZ_TuneCP5_13TeV-pythia8/Fall17V2_ZZ/191023_095447/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listZZ.txt; done

sed -i -e "s/\"/\\\\\"/g" listZZ.txt
sed -i -e "s/\//\\\\\//g" listZZ.txt

#WZ
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WZ_TuneCP5_13TeV-pythia8/Fall17V2_WZ/191023_095721/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWZ.txt; done

sed -i -e "s/\"/\\\\\"/g" listWZ.txt
sed -i -e "s/\//\\\\\//g" listWZ.txt

#WW
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WW_TuneCP5_13TeV-pythia8/Fall17V2_WW/191029_135515/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWW.txt; done

sed -i -e "s/\"/\\\\\"/g" listWW.txt
sed -i -e "s/\//\\\\\//g" listWW.txt


 
#WJets
#100200
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_WJetsHT100To200/191023_100211/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#200400
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_WJetsHT200To400/191023_100439/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#400600
#for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_WJetsHT400To600/191104_104208/0000`;
#do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#600800
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_WJetsHT600To800/191023_100925/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#8001200
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_WJetsHT800To1200/191023_101156/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#12002500
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_WJetsHT1200To2500/191023_101419/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#2500inf
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_WJetsHT2500ToInf/191023_101650/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#incl
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_WJets_1/191023_101914/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_WJets_2/191023_102138/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

sed -i -e "s/\"/\\\\\"/g" listWJets.txt
sed -i -e "s/\//\\\\\//g" listWJets.txt


#Signals
#eejj_L13_M500
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/HavyCompositeMajoranaNeutrino_L13000_M500_mumujj_CalcHep/mumujj_17_L13_M500/191023_104143/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_eejjL13M500.txt; done

sed -i -e "s/\"/\\\\\"/g" list_eejjL13M500.txt
sed -i -e "s/\//\\\\\//g" list_eejjL13M500.txt

#eejj_L13_M1000
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/HavyCompositeMajoranaNeutrino_L13000_M1000_eejj_CalcHep/eejj_17_L13_M1000/191023_103145/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_eejjL13M1000.txt; done

sed -i -e "s/\"/\\\\\"/g" list_eejjL13M1000.txt
sed -i -e "s/\//\\\\\//g" list_eejjL13M1000.txt

#eejj_L13_M2000
#for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /0000`;
#do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_eejjL13M2000.txt; done

#sed -i -e "s/\"/\\\\\"/g" list_eejjL13M2000.txt
#sed -i -e "s/\//\\\\\//g" list_eejjL13M2000.txt

#eejj_L13_M5000
#for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /0000`;
#do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_eejjL13M5000.txt; done

#sed -i -e "s/\"/\\\\\"/g" list_eejjL13M5000.txt
#sed -i -e "s/\//\\\\\//g" list_eejjL13M5000.txt

#eejj_L13_M8000
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/HavyCompositeMajoranaNeutrino_L13000_M8000_eejj_CalcHep/eejj_17_L13_M8000/191023_103909/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_eejjL13M8000.txt; done

sed -i -e "s/\"/\\\\\"/g" list_eejjL13M8000.txt
sed -i -e "s/\//\\\\\//g" list_eejjL13M8000.txt

#mumujj_L13_M500
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/HavyCompositeMajoranaNeutrino_L13000_M500_mumujj_CalcHep/mumujj_17_L13_M500/191023_104143/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_mumujjL13M500.txt; done

sed -i -e "s/\"/\\\\\"/g" list_mumujjL13M500.txt
sed -i -e "s/\//\\\\\//g" list_mumujjL13M500.txt

#mumujj_L13_M1000
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/HavyCompositeMajoranaNeutrino_L13000_M1000_mumujj_CalcHep/mumujj_17_L13_M1000/191023_104415/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_mumujjL13M1000.txt; done

sed -i -e "s/\"/\\\\\"/g" list_mumujjL13M1000.txt
sed -i -e "s/\//\\\\\//g" list_mumujjL13M1000.txt

#mumujj_L13_M2000
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/HavyCompositeMajoranaNeutrino_L13000_M2000_mumujj_CalcHep/mumujj_17_L13_M2000/191023_104644/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_mumujjL13M2000.txt; done

sed -i -e "s/\"/\\\\\"/g" list_mumujjL13M2000.txt
sed -i -e "s/\//\\\\\//g" list_mumujjL13M2000.txt

#mumujj_L13_M5000
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/HavyCompositeMajoranaNeutrino_L13000_M5000_mumujj_CalcHep/mumujj_17_L13_M5000/191023_104909/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_mumujjL13M5000.txt; done

sed -i -e "s/\"/\\\\\"/g" list_mumujjL13M5000.txt
sed -i -e "s/\//\\\\\//g" list_mumujjL13M5000.txt

#mumujj_L13_M8000
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/HavyCompositeMajoranaNeutrino_L13000_M8000_mumujj_CalcHep/mumujj_17_L13_M8000/191023_105135/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_mumujjL13M8000.txt; done

sed -i -e "s/\"/\\\\\"/g" list_mumujjL13M8000.txt
sed -i -e "s/\//\\\\\//g" list_mumujjL13M8000.txt

#DATA
#single ele 
#B
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/SingleElectron/crab_Legacy17V2_SEleBlockB/191101_155742/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_ele_B.txt; done

sed -i -e "s/\"/\\\\\"/g" list_single_ele_B.txt
sed -i -e "s/\//\\\\\//g" list_single_ele_B.txt

#C
#for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /0000`;
#do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_ele_C.txt; done

#sed -i -e "s/\"/\\\\\"/g" list_single_ele_C.txt
#sed -i -e "s/\//\\\\\//g" list_single_ele_C.txt

#D
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/SingleElectron/crab_Legacy17V2_SEleBlockD/191101_160240/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_ele_D.txt; done

sed -i -e "s/\"/\\\\\"/g" list_single_ele_D.txt
sed -i -e "s/\//\\\\\//g" list_single_ele_D.txt

#E
#for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /0000`;
#do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_ele_E.txt; done

#sed -i -e "s/\"/\\\\\"/g" list_single_ele_E.txt
#sed -i -e "s/\//\\\\\//g" list_single_ele_E.txt

#F
#for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /0000`;
#do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_ele_F.txt; done

#sed -i -e "s/\"/\\\\\"/g" list_single_ele_F.txt
#sed -i -e "s/\//\\\\\//g" list_single_ele_F.txt

#single muon 
#B
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/SingleMuon/crab_Legacy17V2_SMuBlockB/191101_161035/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_mu_B.txt; done

sed -i -e "s/\"/\\\\\"/g" list_single_mu_B.txt
sed -i -e "s/\//\\\\\//g" list_single_mu_B.txt

#C
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/SingleMuon/crab_Legacy17V2_SMuBlockC/191101_161322/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_mu_C.txt; done

for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/SingleMuon/crab_Legacy17V2_SMuBlockC/191101_161322/0001`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_mu_C.txt; done

sed -i -e "s/\"/\\\\\"/g" list_single_mu_C.txt
sed -i -e "s/\//\\\\\//g" list_single_mu_C.txt

#D
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/SingleMuon/crab_Legacy17V2_SMuBlockD/191101_161608/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_mu_D.txt; done

sed -i -e "s/\"/\\\\\"/g" list_single_mu_D.txt
sed -i -e "s/\//\\\\\//g" list_single_mu_D.txt


#E
#for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /0000`;
#do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_mu_E.txt; done

#sed -i -e "s/\"/\\\\\"/g" list_single_mu_E.txt
#sed -i -e "s/\//\\\\\//g" list_single_mu_E.txt


#F
#for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /0000`;
#do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> list_single_mu_F.txt; done

#sed -i -e "s/\"/\\\\\"/g" list_single_mu_F.txt
#sed -i -e "s/\//\\\\\//g" list_single_mu_F.txt
