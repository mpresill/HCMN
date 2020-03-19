rm listTT.txt;
rm listST.txt;
rm listZZ.txt;
rm listWZ.txt;
rm listWW.txt;
rm listWJets.txt;
rm listDY.txt;

#TT

for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/Summer16V3_TT/191018_070258/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listTT.txt; done

./conta listTT.txt
sed -i -e "s/\"/\\\\\"/g" listTT.txt
sed -i -e "s/\//\\\\\//g" listTT.txt


#ST

for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/Summer16V3_ST/191018_070514/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listST.txt; done

for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/Summer16V3_SaT/191018_070728/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listST.txt; done

./conta listST.txt
sed -i -e "s/\"/\\\\\"/g" listST.txt
sed -i -e "s/\//\\\\\//g" listST.txt

#ZZ

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/ZZ_TuneCUETP8M1_13TeV-pythia8/Summer16V3_ZZ_1/191018_070942/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listZZ.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/ZZ_TuneCUETP8M1_13TeV-pythia8/Summer16V3_ZZ_2/191018_071159/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listZZ.txt; done

./conta listZZ.txt
sed -i -e "s/\"/\\\\\"/g" listZZ.txt
sed -i -e "s/\//\\\\\//g" listZZ.txt

#WZ

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WZ_TuneCUETP8M1_13TeV-pythia8/Summer16V3_WZ_1/191018_071411/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWZ.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WZ_TuneCUETP8M1_13TeV-pythia8/Summer16V3_WZ_2/191018_071629/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWZ.txt; done
./conta listWZ.txt
sed -i -e "s/\"/\\\\\"/g" listWZ.txt
sed -i -e "s/\//\\\\\//g" listWZ.txt

#WW

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WW_TuneCUETP8M1_13TeV-pythia8/Summer16V3_WW_1/191018_071848/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWW.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WW_TuneCUETP8M1_13TeV-pythia8/Summer16V3_WW_2/191018_072108/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWW.txt; done
./conta listWW.txt
sed -i -e "s/\"/\\\\\"/g" listWW.txt
sed -i -e "s/\//\\\\\//g" listWW.txt

#70100
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT70To100/191023_122829/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

#100200
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT100To200_1/191018_072548/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT100To200_2/191018_072803/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT100To200_3/191018_073037/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

#200400
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT200To400_1/191018_073315/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT200To400_2/191018_073539/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT200To400_3/191018_073802/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

#600800
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT600To800_1/191018_074527/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT600To800_2/191018_074752/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

#8001200
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT800To1200_1/191018_075020/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT800To1200_2/191018_075245/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

#12002500

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT1200To2500_1/191018_075507/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT1200To2500_2/191102_150105/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

#2500Inf

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT2500ToInf_1/191022_122410/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT2500ToInf_2_/191104_185355/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

#incl
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJets_1/191018_092355/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJets_2/191018_092559/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listWJets.txt; done
./conta listWJets.txt
sed -i -e "s/\"/\\\\\"/g" listWJets.txt
sed -i -e "s/\//\\\\\//g" listWJets.txt

#DY
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_DY_1/191018_092805/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listDY.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_DY_2/191018_093011/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> listDY.txt; done
./conta listDY.txt
sed -i -e "s/\"/\\\\\"/g" listDY.txt
sed -i -e "s/\//\\\\\//g" listDY.txt
