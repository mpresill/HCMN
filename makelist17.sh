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
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls `;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#600800
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls `;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#8001200
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls `;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

#incl
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls `;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Summer16V3_WJets_2/191018_092559/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listWJets.txt; done

sed -i -e "s/\"/\\\\\"/g" listWJets.txt
sed -i -e "s/\//\\\\\//g" listWJets.txt

#DY

sed -i -e "s/\"/\\\\\"/g" listDY.txt
sed -i -e "s/\//\\\\\//g" listDY.txt

#TT

sed -i -e "s/\"/\\\\\"/g" listTT.txt
sed -i -e "s/\//\\\\\//g" listTT.txt
