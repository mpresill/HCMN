rm hadd.txt
rm tmp.root

echo "hadd -f WW_2016.root" > hadd.txt

t=0

for i in `ls -altr WW_ | grep root | awk '{print $9}'`;
do

echo "`cat hadd.txt` WW_/$i" > hadd.txt

t=$((t+1))
done
rm tmp.root
`cat hadd.txt`

