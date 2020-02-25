rm list_16_ST.txt;
rm list_16_ZZ.txt;
rm list_16_WZ.txt;
rm list_16_WW.txt;
rm list_16_WJets.txt;

for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/Summer16V3_ST/191018_070514/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_ST.txt; done

for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/Summer16V3_SaT/191018_070728/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_ST.txt; done

sed -i -e "s/\"/\\\\\"/g" list_16_ST.txt
sed -i -e "s/\//\\\\\//g" list_16_ST.txt

#ZZ

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/ZZ_TuneCUETP8M1_13TeV-pythia8/Summer16V3_ZZ_1/191018_070942/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_ZZ.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/ZZ_TuneCUETP8M1_13TeV-pythia8/Summer16V3_ZZ_2/191018_071159/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_ZZ.txt; done

sed -i -e "s/\"/\\\\\"/g" list_16_ZZ.txt
sed -i -e "s/\//\\\\\//g" list_16_ZZ.txt

#WZ

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WZ_TuneCUETP8M1_13TeV-pythia8/Summer16V3_WZ_1/191018_071411/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WZ.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WZ_TuneCUETP8M1_13TeV-pythia8/Summer16V3_WZ_2/191018_071629/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WZ.txt; done

sed -i -e "s/\"/\\\\\"/g" list_16_WZ.txt
sed -i -e "s/\//\\\\\//g" list_16_WZ.txt

#WW

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WW_TuneCUETP8M1_13TeV-pythia8/Summer16V3_WW_1/191018_071848/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WW.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WW_TuneCUETP8M1_13TeV-pythia8/Summer16V3_WW_2/191018_072108/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WW.txt; done

sed -i -e "s/\"/\\\\\"/g" list_16_WW.txt
sed -i -e "s/\//\\\\\//g" list_16_WW.txt

#200400
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT200To400_1/191018_073315/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT200To400_2/191018_073539/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT200To400_3/191018_073802/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WJets.txt; done

#600800
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT600To800_1/191018_074527/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT600To800_2/191018_074752/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WJets.txt; done

#8001200
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT800To1200_1/191018_075020/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJetsHT800To1200_2/191018_075245/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WJets.txt; done

#incl
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJets_1/191018_092355/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJets_2/191018_092559/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_16_WJets.txt; done

sed -i -e "s/\"/\\\\\"/g" list_16_WJets.txt
sed -i -e "s/\//\\\\\//g" list_16_WJets.txt
