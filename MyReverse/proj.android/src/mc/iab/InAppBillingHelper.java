package mc.iab;

import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import mc.bridge.Bridge;
import mc.core.MCLog;
import mc.debug.Debug;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

public class InAppBillingHelper {
    private static final String TAG = "mc-java iab";
    private static final String PREFERENCES_NAME = "mclibiabpref"; // SharedPreferenceの名前
    private static final String PREFERENCES_SEPARATOR = "___IABSEP___"; // SharedPreferenceの文字列データを分けるセパレータ
    public  static final String SKU_ANDROID_TEST_PURCHASE = "android.test.purchased";
    
    // Googleストアから購入データを取得したら、即時消費する
    private static final boolean IMMEDIATE_CONSUME = Debug.ON && false;
    
    // IabHelper のログ出力フラグ
    private static final boolean DEBUG_LOG_IAB_HELPER = Debug.LOG && false;
    
    private static final boolean DEBUG_LOG = Debug.LOG && false;
    
    // (arbitrary) request code for the purchase flow
    public static final int IN_APP_BILLING_REQUEST_CODE = 200023;
    
    private String _lastProductId; // purchaseメソッドで購入しようとした最後のプロダクトID
    private boolean _isSetupFinished = false;
    private boolean _isQueryInventoryFinished = false;
    
    private Activity _activity;
    private IabHelper _helper;
    private Inventory _inventory;
    
    // ストアで購入済み、かつ未消費のアイテム
    private final Map<String, Purchase> _purchasedItemMap = new HashMap<String, Purchase>();

    private static void logv(String format, Object... args) {
        if (DEBUG_LOG) {
            MCLog.vWithTag(TAG, format, args);
        }
    }
    
    private static void logd(String format, Object... args) {
        if (DEBUG_LOG) {
            MCLog.dWithTag(TAG, format, args);
        }
    }
    
    @SuppressWarnings("unused")
    private static void logi(String format, Object... args) {
        if (DEBUG_LOG) {
            MCLog.iWithTag(TAG, format, args);
        }
    }

    private static void logw(String format, Object... args) {
        if (DEBUG_LOG) {
            MCLog.wWithTag(TAG, format, args);
        }
    }
    
    private static void loge(String format, Object... args) {
        if (DEBUG_LOG) {
            MCLog.eWithTag(TAG, format, args);
        }
    }
    
    /**
     * SharedPreferencesに購入データ(レシート、シグネチャ)を保存します。
     * 
     * @param productId プロダクトID
     * @param purchase 購入データ
     */
    private void savePurchaseToSharedPreferences(String productId, Purchase purchase) {
        SharedPreferences pref = _activity.getSharedPreferences(PREFERENCES_NAME, Context.MODE_PRIVATE);
        Editor e = pref.edit();
        String value = purchase.getOriginalJson() + PREFERENCES_SEPARATOR + purchase.getSignature();
        e.putString(productId, value);
        e.commit();
    }
    
    /**
     * SharedPreferencesから購入データを削除します。
     * 
     * @param productId プロダクトID
     */
    private void removePurchaseFromSharedPreferences(String productId) {
        SharedPreferences pref = _activity.getSharedPreferences(PREFERENCES_NAME, Context.MODE_PRIVATE);
        Editor e = pref.edit();
        e.remove(productId);
        e.commit();
    }
    
    /**
     * Googleライブラリの初期化が完了したかどうか
     * 
     * @return 完了済みならtrue
     */
    public boolean isSetupFinished() {
        return _isSetupFinished;
    }
    
    /**
     * Googleライブラリの初期化後の、未消費の購入データの存在チェックが完了したかどうか
     * 
     * @return 完了済みならtrue
     */
    public boolean isQueryInventoryFinished() {
        return _isQueryInventoryFinished;
    }
    
    public InAppBillingHelper(Activity activity) {
        final String base64PublicKey = ""; // レシート検証はアプリサーバーで行うため、アプリ内で公開鍵を保持する必要はない
        _activity = activity;
        _helper = new IabHelper(activity, base64PublicKey);
        _helper.enableDebugLogging(DEBUG_LOG_IAB_HELPER);
        
        _helper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
            @Override
            public void onIabSetupFinished(IabResult result) {
                logv("setup finished");
                _isSetupFinished = true;
                
                if (!result.isSuccess()) {
                    loge("Problem setting up in-app billing");
                    return;
                }
                _helper.queryInventoryAsync(_gotInventoryListener);
            }
        });
    }
    
    public void dispose() {
        if (_helper != null) {
            _helper.dispose();
        }
        _helper = null;
    }
    
    private void consumeAsync(final Purchase purchase) {
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                _helper.consumeAsync(purchase, _consumeFinishedListener);
            }
        });
    }
    
    /**
     * ストアでの購入処理へ遷移可能かどうか
     * 
     * @return 可能ならtrue
     */
    public boolean canMakePayments() {
        return _isSetupFinished && _isQueryInventoryFinished;
    }
    
    /**
     * ストアでの消費型アイテムの購入処理を開始します。
     * 
     * @param productId プロダクトID
     */
    public void purchase(String productId) {
        if (!canMakePayments()) {
            loge("Purcahse cant start. (canMakePayments is false)");
            return;
        }
        logv("Launching purchase flow for consumed item.");
        
        /* TODO: for security, generate your payload here for verification. See the comments on
         *       verifyDeveloperPayload() for more info. Since this is a SAMPLE, we just use
         *       an empty string, but on a production app you should carefully generate this.
         */
        final String payload = "";
        _lastProductId = productId;
        _helper.launchPurchaseFlow(_activity, productId, IN_APP_BILLING_REQUEST_CODE, _purchaseFinishedListener, payload);
    }
    
    /**
     * 消費型アイテムの購入処理を完了します。
     * (アプリサーバへアイテム反映が完了後にコールしてください)
     * 
     * @param productId プロダクトID
     */
    public void finish(String productId) {
        Purchase purchase = _purchasedItemMap.get(productId);
        if (purchase == null) {
            logw("Purchase NOT FOUND. productId:[%s]", productId);
        }
        else {
            logd("CONSUME START: prodcutId:[%s]", productId);
            consumeAsync(purchase);
        }
    }
    
    /**
     * ストアで購入済み、かつ未消費のアイテムがあるかチェックします。
     * もしそのようなアイテムがある場合は、その購入データが、
     * C++ のコールバックオブジェクトにコールバックされます。
     */
    public void queryInventory() {
        logv("========== QUWRY INVENTORY BEGIN ==========");
        SharedPreferences pref = _activity.getSharedPreferences(PREFERENCES_NAME, Context.MODE_PRIVATE);
        Map<String, ?> map = pref.getAll();
        
        // C++側にコールバックされたプロダクトIDの集合
        HashSet<String> sentProductIds = new HashSet<String>();

        for (String productId : map.keySet()) {
            logv("SHAREDPREFERENCES key:[%s]", productId);
            String s = (String)map.get(productId);
            String[] xs = s.split(PREFERENCES_SEPARATOR, -1);
            
            if (xs.length == 2) {
                String originalJson = xs[0];
                String signature = xs[1];
                
                logv("---- query inventory (SharedPreferences)----");
                logv("  productId:[%s]", productId);
                logv("  oroginalJson:[%s]", originalJson);
                logv("  signature:[%s]", signature);
                logv("-------------------------");
                
                Bridge.nativeIabOnPurchased(productId, originalJson, signature);
                sentProductIds.add(productId);
            }
        }
        
        for (Entry<String, Purchase> entry : _purchasedItemMap.entrySet()) {
            String productId = entry.getKey();
            Purchase purchase = entry.getValue();

            if (!sentProductIds.contains(productId)) {
                logv("---- query inventory (_purchasedItemMap) ----");
                logv("  productId:[%s]", productId);
                logv("  originalJson:[%s]", purchase.getOriginalJson());
                logv("  signature:[%s]", purchase.getSignature());
                logv("-----------------------");
                Bridge.nativeIabOnPurchased(productId, purchase.getOriginalJson(), purchase.getSignature());
                sentProductIds.add(productId);
            }
        }
        
        logd("---------- queryInventory count:%d _purchasedItemMap.size():%d----------", sentProductIds.size(), _purchasedItemMap.size());
        logv("========== QUERY INVENTORY END ==========");
    }
    
    public boolean verifyDeveloperPayload(Purchase purchase) {
        // String payload = purchase.getDeveloperPayload();
        
        /*
         * TODO: verify that the developer payload of the purchase is correct. It will be
         * the same one that you sent when initiating the purchase.
         * 
         * WARNING: Locally generating a random string when starting a purchase and
         * verifying it here might seem like a good approach, but this will fail in the
         * case where the user purchases an item on one device and then uses your app on
         * a different device, because on the other device you will not have access to the
         * random string you originally generated.
         * 
         * So a good developer payload has these characteristics:
         * 
         * 1. If two different users purchase an item, the payload is different between them,
         *    so that one user's purchase can't be replayed to another user.
         * 
         * 2. The payload must be such that you can verify it even when the app wasn't the
         *    one who initiated the purchase flow (so that items purchased by the user on
         *    one device work on other devices owned by the user).
         * 
         * Using your own server to store and verify develoerp payloads across app
         * installations is recommended.
         */
        return true;
    }
    
    // Listener that's called when we finish quwrying the items and subscriptions we own
    IabHelper.QueryInventoryFinishedListener _gotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
        @Override
        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
            logd("query inventory finished SUCCESS:%s", result.isSuccess());
            
            if (result.isFailure()) {
                loge("Failed to query inventory: " + result);
                _isQueryInventoryFinished = true;
                return;
            }
            
            List<String> ownedSkus = inventory.getAllOwnedSkus();
            for (String sku : ownedSkus) {
                logd("OWNED: productId:[%s]", sku);
                
                Purchase purchase = inventory.getPurchase(sku);
                if (IMMEDIATE_CONSUME) {
                    logw("IMMEDIATE CONSUME");
                    consumeAsync(purchase);
                }
                else {
                    if (purchase != null) {
                        _purchasedItemMap.put(sku, purchase);
                        savePurchaseToSharedPreferences(sku, purchase);
                    }
                }
            }
            
            _inventory = inventory;
            _isQueryInventoryFinished = true;
        }
    };
    
    IabHelper.OnIabPurchaseFinishedListener _purchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
        @Override
        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
            logd("##### onIabPurchaseFinished #####");
            logd("  SUCCESS:%s [%s]", result.isSuccess(), result.toString());
                        
            if (result.isSuccess()) { // 購入処理、成功
                final String productId = purchase.getSku();
                final String receipt   = purchase.getOriginalJson();
                final String signature = purchase.getSignature();
                
                if (IMMEDIATE_CONSUME) { // 即時消費(デバッグ用)
                    logw("IMMEDIATE CONSUME");
                    consumeAsync(purchase);
                }
                else {
                    _purchasedItemMap.put(productId, purchase);
                    savePurchaseToSharedPreferences(productId, purchase);
                    
                    Bridge.nativeIabOnPurchased(productId, receipt, signature); // C++ へコールバック
                }
            }
            else { // 購入、不成功
                logw("Error purchasing: " + result);
                
                final int response = result.getResponse();
                switch (response) {
                case IabHelper.BILLING_RESPONSE_RESULT_ITEM_ALREADY_OWNED:
                    // 既に所有済みのアイテムに対して、再購入処理が行われた
                    // (未消費のアイテムが存在している場合に、同じアイテムに対して購入処理が開始された)
                    Bridge.nativeIabOnPurchaseFailed(_lastProductId, response);
                    break;
                    
                case IabHelper.IABHELPER_USER_CANCELLED:
                    Bridge.nativeIabOnCancelled(_lastProductId);
                    break;

                case IabHelper.IABHELPER_BAD_RESPONSE:
                    logd("result.getResponse() == IabHelper.IABHELPER_BAD_RESPONSE");
                    Bridge.nativeIabOnPurchaseFailed(_lastProductId, response);
                    
                    // FIXME 購入処理中にサスペンドすると、たとえ購入処理が正しく完了していたとしても
                    // bad response received が渡される場合がある
                    break;
                    
                default:
                    loge("unknown response:%d", result.getResponse());
                    Bridge.nativeIabOnPurchaseFailed(_lastProductId, response);
                    break;
                }
            }

//          if (!verifyDeveloperPayload(purchase)) {
//              loge("Error purchasing. Authenticity verification failed.");
//          }
        }
    };
    
    IabHelper.OnConsumeFinishedListener _consumeFinishedListener = new IabHelper.OnConsumeFinishedListener() {
        @Override
        public void onConsumeFinished(Purchase purchase, IabResult result) {
            logd("##### onConsumeFinished #####");
            logd("  SUCCESS:%s productId:[%s]", result.isSuccess(), purchase.getSku());

            if (result.isSuccess()) {
                logd("Consumption successful. Provisioning.");
                String productId = purchase.getSku();
                if (_purchasedItemMap.remove(productId) != null) {
                    logv("REMOVED _purchasedItemMap productId:[%s]", productId);
                }
                removePurchaseFromSharedPreferences(productId);
            }
            
            logd("End consumption flow.");
        }
    };
    
    public boolean handleActivityResult(int requestCode, int resultCode, Intent data) {
        logd("handleActivityResult resuestCode:%d resultCode:%d", requestCode, resultCode);
        return _helper.handleActivityResult(requestCode, resultCode, data);
    }

    // ----- テスト -----
    
//    public void test_verifyPurchase() {
//        // ローカルでの署名検証チェック用
//        String base64PublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAs1vftO6wtCxXHSf0H8FshrbdV3+NyvLmh8pb+nlIqCF5vEUYtDaUR7JK7sSQ0pzzsFKd6AIsrlhF1X728rqchs/FSKU5DgrJ0j+dpumVJRw+eWkeiJQH7Qf4CCs0gTkt+VfoEhh+Zg7u+MVKcRYGgkTUrUqWNTCLJC8+VA02Lwy6oOrqbP965gxsJHOyJxkDQe7pvvd2NGmMC4Bns3mYhf2+J6xcpuHg2hsQ2NZjj6fEPpFidQIx1izEOaSctqWCKMk09p+S95IuZ16LaauuCu6sNI1ze6uaa6Jjw+N5bTjmeEhUnErsAEBEH3YDm5SZ04lDUN3O0mCVXS2GLTgVwQIDAQAB";
//        String purchase = "{\"orderId\":\"12999763169054705758.1306469434975951\",\"packageName\":\"jp.co.fwinc.drider\",\"productId\":\"uay8btr4ba\",\"purchaseTime\":1377686788000,\"purchaseState\":0,\"purchaseToken\":\"dnvfumizsfsqwqkrlstgfisj.AO-J1OzmtA52tTQ0z2Nbf7S43Npluykp-sRH2gczWS8Db59miujV7X1iCfYoLRTiNrDdW3suJ6VXP-jgIsQfYDKA63sWwSz1SfO5KrSlMgHLSvzl0n4-V-k\"}";
//        String signature = "b3R0NZV4JUBIkDMdx6pJGT+/waVTdYqj5g3KO2LbI8xUDLN5ZkpJHwiy6nnC3H2FrqJzXr80jbXQwP1Ab5dsN2HrSV6KIUVkNn0gnXHzWSatsBj+mtHqKNdIN9xojheha9T0tWgYDSyOuJW5ZjAfzEQgRCSUXd1Yehs82ixAHUtn1j+QbmJJKQOzlI0SDhd8muFMYY1uw/TXdIX8XEjC6+glV4O6UEBJ9QhRKU6wreflTP7z7Ounu0ywQZzRYUr7Tl7tZoh4UuYp4O2TIKLbrT08BXdNqrKbLc08E+q8So9DBZY3POTYB1vS6Z68GT19bcDqcVq91sZ+vuw7Y0dBaQ==";
//
//        java.security.PublicKey key = Security.generatePublicKey(base64PublicKey);
//        boolean verified = Security.verify(key, purchase, signature);
//        logd("---- VERIFY PURCHASE:%s ----", Boolean.toString(verified));
//    }
    
}


