rm hadd.txt
rm tmp.root

echo "hadd -f WW_2016.root" > hadd.txt #EDIT: change name of the final root file

t=0

for i in `ls -altr WW_ | grep root | awk '{print $9}'`; #EDIT: name of the task (the "hadd.sh" needs to stay in the output folder)
do

echo "`cat hadd.txt` WW_/$i" > hadd.txt

t=$((t+1))
done
rm tmp.root
`cat hadd.txt`

