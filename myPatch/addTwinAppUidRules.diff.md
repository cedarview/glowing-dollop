```
From 4213811da861a3d43e86215368b1850e2b98d86b Mon Sep 17 00:00:00 2001
From: darview_cheng <Darview_Cheng@asus.com>
Date: Wed, 28 Jun 2017 14:15:50 +0800
Subject: [PATCH] [BSP][8953][DOZE]Only add twinApp's uid to fw_dozable

Change-Id: Iffd991d8f7fcbbb055134a00029ea67e8ed8662e
Reviewed-on: http://172.29.0.92:8443/86989
Reviewed-by: Vector Xiang(項亮_華碩蘇州) <Vector_Xiang@asus.com>
---

diff --git a/services/core/java/com/android/server/net/NetworkPolicyManagerService.java b/services/core/java/com/android/server/net/NetworkPolicyManagerService.java
index 7f8b1d1..7170314 100644
--- a/services/core/java/com/android/server/net/NetworkPolicyManagerService.java
+++ b/services/core/java/com/android/server/net/NetworkPolicyManagerService.java
@@ -163,6 +163,7 @@
 import android.util.SparseIntArray;
 import android.util.TrustedTime;
 import android.util.Xml;
+import android.content.pm.ResolveInfo;
 
 import com.android.internal.R;
 import com.android.internal.annotations.GuardedBy;
@@ -2747,6 +2748,26 @@
         updateRulesForWhitelistedPowerSaveUL(uid, mDeviceIdleMode, FIREWALL_CHAIN_DOZABLE);
     }
 
+    //ASUS_bsp++  update twin_app_user's app rules
+    private SparseIntArray getTwinAppsId(int twinUserId){
+        final SparseIntArray desTwinAppIds = new SparseIntArray();
+        if(twinUserId != -1){
+            Intent mainIntent = new Intent(Intent.ACTION_MAIN, null);
+            mainIntent.addCategory(Intent.CATEGORY_LAUNCHER);
+            List<ResolveInfo> apps = mContext.getPackageManager().queryIntentActivities(mainIntent, 0);
+            for(ResolveInfo list : apps) {
+	        int uid = list.activityInfo.applicationInfo.uid;
+                int userId = UserHandle.getUserId(uid);
+	        int appId = UserHandle.getAppId(uid);
+	        if(userId == twinUserId){
+		    desTwinAppIds.put(appId, userId);
+	        }
+            }
+        }
+        return desTwinAppIds;
+    }
+    //ASUS_bsp--  update twin_app_user's app rules
+
     // NOTE: since both fw_dozable and fw_powersave uses the same map
     // (mPowerSaveTempWhitelistAppIds) for whitelisting, we can reuse their logic in this method.
     private void updateRulesForWhitelistedPowerSaveUL(boolean enabled, int chain,
@@ -2775,22 +2796,23 @@
 	    //ASUS_bsp++  update twin_app_user's app rules
 	    if(android.os.Build.FEATURES.ENABLE_TWIN_APPS)
 	    {
-                Slog.d(TAG,"Update twin_app_user's app to uidRules");
                 int twinAppUserId = mUserManager.getTwinAppsId();
                 if(twinAppUserId != -1)
                 {
-	                for (int i = mPowerSaveTempWhitelistAppIds.size() - 1; i >= 0; i--) {
-	                    if (mPowerSaveTempWhitelistAppIds.valueAt(i)) {
-	                        int appId = mPowerSaveTempWhitelistAppIds.keyAt(i);
-	                        int uid = UserHandle.getUid(twinAppUserId, appId);
-	                        uidRules.put(uid, FIREWALL_RULE_ALLOW);
-	                    }
-	                }
-	                for (int i = mPowerSaveWhitelistAppIds.size() - 1; i >= 0; i--) {
-	                    int appId = mPowerSaveWhitelistAppIds.keyAt(i);
-	                    int uid = UserHandle.getUid(twinAppUserId, appId);
-	                    uidRules.put(uid, FIREWALL_RULE_ALLOW);
-	                }
+                    final SparseIntArray twinAppIds = getTwinAppsId(twinAppUserId);
+                    if(twinAppIds.size() != 0){
+                        if(LOGD){
+                            Slog.i(TAG,"Update twin_app_user's app to uidRules. twinAppIds="+twinAppIds.toString());
+                        }
+                        for (int i = twinAppIds.size() -1; i>=0; i--){
+                            int appId = twinAppIds.keyAt(i);
+                            int uid = UserHandle.getUid(twinAppUserId, appId);
+                            if(mPowerSaveTempWhitelistAppIds.get(appId,false) || mPowerSaveWhitelistAppIds.get(appId,false)){
+                                uidRules.put(uid, FIREWALL_RULE_ALLOW);
+                                Slog.i(TAG,"add uidRules allow for twinAPP uid="+uid);
+                            }
+                        }
+                    }
                 }
 	    }
 	    //ASUS_bsp--  update twin_app_user's app rules
```
