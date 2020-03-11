rm list_2016_data_mu_B.txt;
rm list_2016_data_mu_C.txt;
rm list_2016_data_mu_D.txt;
rm list_2016_data_mu_E.txt;
rm list_2016_data_mu_F.txt;
rm list_2016_data_mu_G.txt;
rm list_2016_data_mu_H.txt;
rm list_2016_data_ele_B.txt;
rm list_2016_data_ele_C.txt;
rm list_2016_data_ele_D.txt;
rm list_2016_data_ele_E.txt;
rm list_2016_data_ele_F.txt;
rm list_2016_data_ele_G.txt;
rm list_2016_data_ele_H.txt;

#Single Muon B

for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockB/191019_142024/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_B.txt; done
for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockB/191019_142024/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_B.txt; done
for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockB/191019_142024/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_B.txt; done
for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockB_recov/191025_074213/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_B.txt; done
sed -i -e "s/\"/\\\\\"/g" list_2016_data_mu_B.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_mu_B.txt

#Single Muon C

for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockC/191019_142249/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_C.txt; done
for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockC/191019_142249/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_C.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_mu_C.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_mu_C.txt

#Single Muon D

for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockD/191019_142524/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_D.txt; done
for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockD/191019_142524/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_D.txt; done
for i in `xrdfs root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockD/191019_142524/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_D.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_mu_D.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_mu_D.txt

#Single Muon E

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockE/191019_142752/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_E.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockE/191019_142752/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_E.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_mu_E.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_mu_E.txt

#Single Muon F

for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockF/191019_143022/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_F.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockF/191019_143022/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_F.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockF_recov/191025_073607/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_F.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_mu_F.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_mu_F.txt

#Single Muon G
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockG/191019_143254/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_G.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockG/191019_143254/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_G.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockG/191019_143254/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_G.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockG/191019_143254/0003`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_G.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockG_recov/191030_155952/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_G.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_mu_G.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_mu_G.txt

#Single Muon H
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockH/191031_162355/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_H.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockH/191031_162355/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_H.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockH/191031_162355/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_H.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockH/191031_162355/0003`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_H.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleMuon/crab_Summer16V11_SMuBlockH/191031_162355/0004`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_mu_H.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_mu_H.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_mu_H.txt

#Single Ele B
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockB/191019_140339/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_B.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockB/191019_140339/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_B.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockB/191019_140339/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_B.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockB/191019_140339/0003`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_B.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockB/191019_140339/0004`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_B.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockB/191019_140339/0005`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_B.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockB_recov/191025_080644/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_B.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_ele_B.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_ele_B.txt 

#Single Ele C
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockC/191019_140603/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_C.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockC/191019_140603/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_C.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockC/191019_140603/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_C.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_ele_C.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_ele_C.txt

#Single Ele D 
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockD/191019_140822/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_D.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockD/191019_140822/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_D.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockD/191019_140822/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_D.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockD/191019_140822/0003`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_D.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_ele_D.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_ele_D.txt

#Single Ele E 
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockE/191019_141041/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_E.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockE/191019_141041/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_E.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockE/191019_141041/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_E.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockE/191019_141041/0003`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_E.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockE/191019_141041/0004`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_E.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_ele_E.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_ele_E.txt

#Single Ele F
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockF/191019_141306/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_F.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockF/191019_141306/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_F.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_ele_F.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_ele_F.txt

#Single Ele G
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockG/191019_141532/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_G.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockG/191019_141532/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_G.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockG/191019_141532/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_G.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockG/191019_141532/0003`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_G.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockG_recov/191030_160422/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_G.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_ele_G.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_ele_G.txt

#Single Ele H
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockH/191019_141801/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_H.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockH/191019_141801/0001`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_H.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockH/191019_141801/0002`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_H.txt; done
for i in `xrdfs  root://ss-03.recas.ba.infn.it:8080 ls /store/user/vmariani/SingleElectron/crab_Summer16V11_SEleBlockH_recov/191025_074932/0000`;
do echo "root://ss-03.recas.ba.infn.it:8080/${i//\/cms/}" >> list_2016_data_ele_H.txt; done

sed -i -e "s/\"/\\\\\"/g" list_2016_data_ele_H.txt
sed -i -e "s/\//\\\\\//g" list_2016_data_ele_H.txt
