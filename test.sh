
dict="./dictionaries/webster"
i=0
while read dict;
do
    word="$dict" 
    ./ok "$word" 1> /dev/null
    ((i++))
    if [ $? -eq 99 ]
    then
        echo "$word giving an error" >> problems.txt
    fi
done < "$dict"


echo $i
if [ 20422 -eq $i ]
then
    echo "count and i and equal"
else
    echo "count and i aren't equal"
fi 



