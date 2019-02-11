dict="./dictionaries/tiny"
num=`wc $dict | awk '{print $1}'`
echo $num
