```
#!/system/bin/sh

svc power stayon true

mkdir -p sdcard/ATST/ToolInfo
if [ ! -e sdcard/darview ];then
    mkdir -p sdcard/darview
fi

if [ ! -e sdcard/darview/mylog ];then
    mkdir sdcard/darview/mylog
fi
cp -a /data/logcat_log/ /sdcard/darview/

y=1
z=30

while :
do
    #logcat.txt.01,logcat.txt是最新的，之前的从30开始，序号越大越新，20之前的和以前一样
    if [ -e /data/logcat_log/logcat.txt.01 ]; then
        if [ /data/logcat_log/logcat.txt.01 -nt /sdcard/darview/logcat_log/logcat.txt ]; then
            if [ -e /sdcard/darview/logcat_log/logcat.txt.01 ]; then
                cp /sdcard/darview/logcat_log/logcat.txt.01 /sdcard/darview/logcat_log/logcat.txt."$z"
            fi
            cp /data/logcat_log/logcat.txt.01 /sdcard/darview/logcat_log/logcat.txt.01
            cp /data/logcat_log/logcat.txt /sdcard/darview/logcat_log/logcat.txt
            z=$(($z+1))
        fi
    fi

	rm -f /sdcard/ATST/ToolInfo/APIResult		
   	svc wifi enable
	sleep 3
	sleep 3	
	sleep 4
	sleep 5
    x=1
	echo "$(date) : start connect "
	am startservice --user 0 -n com.asus.at/.MainService -a ConnectToWiFiAP -e Ap "12345678" -e Pwd "12345678" -e Protocol "WPA"
	
	while [ $x -le 240 ]
	do

		rm -f /sdcard/ATST/ToolInfo/APIResult
		am startservice --user 0 -n com.asus.at/.MainService -a IsWiFiConnected
		fstatus=$(cat sdcard/ATST/ToolInfo/APIResult)		   
	   if [ "$fstatus" == "true" ]; then
		  echo "connect success $y!"
		  break					  
	   else
		  sleep 2
		  x=$(($x+1))
	   fi
	done

	echo "x is $x"
	if [ $x == 241 ]; then
		echo "$(date) :connect fail! y= $y!"
		screencap -p /sdcard/darview/wifi_fail"$y".png
		dumpsys wifi > /sdcard/darview/mylog/wifi.log."$y"
		date >>sdcard/darview/myerror.txt
		echo "failed on y=$y date is : $(date)" >>sdcard/darview/myerror.txt
		#cp -a /data/logcat_log/ /sdcard/darview/mylog"$y"/

		#exit 1
	fi
	
	#echo "connect success $y!"
	sleep 2
	
	am startservice --user 0 -n com.asus.at/.MainService -a RemoveAllWiFiConfiguredNetworks
	
	sleep 3
	svc wifi disable   	
	sleep 3
	y=$(($y+1))
done
```
