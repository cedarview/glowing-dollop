```
#!/system/bin/sh

#s=$(awk '{print $2}' logcat.txt.01 |cut -d ":" -f 1)
#找到指定行，从指定行数中间进行搜索
#s=$(cat -n logcat.txt |awk '{print $1}')
#for i in $s
#do
    #效率太底而且不能显示行号，都为1，哈哈
#    if [ $i -gt 8525 ];then
#        grep -i -r $i logcat.txt |grep -i -n "KERNEL  :"
#    fi
#done

#type the keyword more accurate to speed up,,s is a series number of keywork occurred line
#stofind=""
#startline=71006
#endline=80067
#stringtofind="SoftApManager:|hostapd : wlan0: AP|SoftapController:"

startline=$1
endline=$2
stringtofind=$3
stringfiletofind=$4

echo "the string you want to find is \"$stringtofind\" startline=$startline endline=$endline the fiel=$stringfiletofind"
s=$(grep -i -n -E "$stringtofind" "$stringfiletofind" |cut -d ":" -f 1)
#echo 1
#echo $s
for i in $s
do
    #the line start
    if [ $i -ge $startline ]; then
        if [ $i -le $endline ]; then
            #grep from the file every time,,and grep the line number that same as the number
            grep -i -n -E "$stringtofind" "$stringfiletofind" |grep $i
        fi
    fi    
done

exit 0
```
