```
From 5c80be31c2d573cd264f1f3512ece7ed4bd06bac Mon Sep 17 00:00:00 2001
From: darview_cheng <Darview_Cheng@asus.com>
Date: Tue, 21 Feb 2017 14:17:11 +0800
Subject: [PATCH] [BSP][ZS550KL][WIFI]Set wifi mac when do not have factory file

Change-Id: I40682cd9c78488b60881ecc2b513594e5744f977
Reviewed-on: http://172.29.0.92:8443/67658
Reviewed-by: Vector Xiang(項亮_華碩蘇州) <Vector_Xiang@asus.com>
---

diff --git a/wcnss-service/wcnss_service.c b/wcnss-service/wcnss_service.c
index 10595cb..603715c 100644
--- a/wcnss-service/wcnss_service.c
+++ b/wcnss-service/wcnss_service.c
@@ -45,6 +45,10 @@
 #include "mdm_detect.h"
 #endif
 
+//BSP++ set mac address when factorymac do not exist
+#include <sys/time.h>
+//BSP-- set mac address when factorymac do not exist
+
 #define SUCCESS 0
 #define FAILED -1
 #define BYTE_0  0
@@ -304,6 +308,29 @@
 	chdir("..");
 }
 
+//ASUS BSP++ set_mac_when factorymac file do not exist
+void set_mac_when_factoryfile_do_not_exist(char mac_buf_to_write[4][30])
+{
+	char my_mac_buf[max_size];
+        int random[6]={0,0,0,0,0,0};
+	int myrandomcount=0;
+	struct timeval tiem_seed;
+	int my_random_seed;
+	char *my_wrap_str = "\n";
+
+	gettimeofday( &tiem_seed, NULL );
+	my_random_seed=tiem_seed.tv_usec;
+	srand(my_random_seed);
+	for(myrandomcount=0;myrandomcount<6;myrandomcount++)
+	{
+	    random[myrandomcount]=rand() % 16;
+	}
+	sprintf(my_mac_buf,"%s%s%X%X%X%X%X%X",mac_cmp_buf[0],"000AF5",random[0],random[1],random[2],random[3],random[4],random[5]);
+        strncat(mac_buf_to_write[0],my_mac_buf,28);
+	strcat(mac_buf_to_write[0],my_wrap_str);
+}
+//ASUS BSP-- set_mac_when factorymac file do not exist
+
 int get_mac_address(int invaild_mac_flag[4],char mac_buf[4][30])
 {
 	FILE *fp;
@@ -313,19 +340,25 @@
 	int i = 0;
 	int n;
 	int size;
-	
+
 	fp = fopen(MAC_FILE_NAME,"r");
 	if(fp==NULL)
 	{
 		ALOGE("Failed to open mac file:  %s %s",MAC_FILE_NAME, strerror(errno));
-		return 1;
+		//ASUS BSP++ set_mac_when factorymac file do not exist
+		set_mac_when_factoryfile_do_not_exist(mac_buf);
+		invaild_mac_flag[1] = 1;
+		invaild_mac_flag[2] = 1;
+		invaild_mac_flag[3] = 1;
+		return 0;
+		//ASUS BSP-- set_mac_when factorymac file do not exist
 	}
-	ALOGI("Success to open mac file: %s",MAC_FILE_NAME);	
+	ALOGI("Success to open mac file: %s",MAC_FILE_NAME);
 	while(fgets(buf,max_size,fp)!=NULL)
 	{
 		if(i>3)
 			break;
-		size = 0;	
+		size = 0;
 		while(buf[size] != '\n')
 		{
 			size++;
@@ -335,18 +368,18 @@
 		{
 			ALOGE("mac[%d] is invaild,please check buf size",i);
 		}
-		
+
 		for(n=0;n<size;n++)
 		{
 			char temp = toupper(buf[n]);
 			buf[n] = temp;
 		}
-			
+
 		if(strncmp(buf,invaild_mac_buf,12)==0||size != 12)
 		{
 			invaild_mac_flag[i] = 1;
 		}
-			
+
 		strcpy(mac_buf[i],mac_cmp_buf[i]);
 		strncat(mac_buf[i],buf,size);
 		strcat(mac_buf[i],wrap_str);
@@ -396,7 +429,7 @@
 	char country_code_str[PROPERTY_VALUE_MAX];		//<asus-kevin>150519+
 	int country_code_failed_flag = 0;
 	int mac_file_failed_flag = 0;
-	
+
 	mac_file_failed_flag = get_mac_address(invaild_mac_flag,mac_buf);
 	country_code_failed_flag = get_country_code(ap_country_buf,sta_country_buf,country_code_str);	//<asus-kevin>150519+
 	fp_source = fopen(WLAN_INI_FILE_SOURCE,"r");
```
