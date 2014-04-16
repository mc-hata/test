package mc.bridge;

import mc.core.MCLog;
import mc.iab.InAppBillingHelper;
import android.app.Activity;

public class Bridge {
    // @SuppressWarnings("unused")
    private static Activity _activity;
    private static InAppBillingHelper _iabHelper;
        
    public static void init(Activity activity, InAppBillingHelper iabHelper) {
        _activity = activity;
        _iabHelper = iabHelper;
    }
    
    // ---------- In-App Billing ----------
    
    public static boolean iab_canMakePayments() {
        if (_iabHelper == null) {
            MCLog.e("_iabHelper is null");
            return false;
        }
        
        return _iabHelper.canMakePayments();
    }

    public static void iab_purchase(String productId) {
        if (_iabHelper == null) {
            MCLog.e("_iabHelper is null");
            return;
        }
        
        _iabHelper.purchase(productId);
    }
    
    public static void iab_finish(String productId) {
        if (_iabHelper == null) {
            MCLog.e("_iabHelper is null");
            return;
        }
        
        _iabHelper.finish(productId);
    }
    
    public static void iab_queryInventory() {
        if (_iabHelper == null) {
            MCLog.e("_iabHelper is null");
            return;
        }
        
        _iabHelper.queryInventory();
    }
    
    native public static void nativeIabOnPurchased(String productId, String receipt, String signature);
    native public static void nativeIabOnCancelled(String productId);
    native public static void nativeIabOnPurchaseFailed(String productId, int errorCode);
}
