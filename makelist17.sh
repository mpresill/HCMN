# to find sample path in Legnaro:
# xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill
#rm listST.txt;
#rm listZZ.txt;
#rm listWZ.txt;
#rm listWW.txt;
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
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listDY.txt

for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/Fall17V2_DY2/191023_102649/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listDY.txt

sed -i -e "s/\"/\\\\\"/g" listDY.txt
sed -i -e "s/\//\\\\\//g" listDY.txt

#TT
for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/Fall17V2_TT/191022_133904/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listTT.txt; done

for i in `xrdfs root://t2-xrdcms.lnl.infn.it:7070 ls /store/user/mpresill/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/Fall17V2_TT/191023_094710/0000`;
do echo "root://t2-xrdcms.lnl.infn.it:7070/${i//\/cms/}" >> listTT.txt; done

sed -i -e "s/\"/\\\\\"/g" listTT.txt
sed -i -e "s/\//\\\\\//g" listTT.txt

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
