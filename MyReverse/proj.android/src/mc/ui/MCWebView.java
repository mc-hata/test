package mc.ui;

import java.util.List;

import mc.core.MCLog;
import mc.core.Res;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.ResolveInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.net.Uri;
import android.webkit.WebChromeClient;
import android.webkit.WebSettings;
import android.webkit.WebViewClient;
import android.webkit.WebView;
import android.widget.ImageButton;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.view.View;

public class MCWebView {    
    private Activity _activity;
    private RelativeLayout _parentView;
    private WebView _webView;    
    private ImageButton _exitButton;  // 閉じるボタン
    private ProgressBar _progressBar; // ページ読み込み中のインジケータ   
    private boolean _isOpen; // WebViewが開いているかどうか
        
    private final int PROGRESS_BAR_SIZE = 70;
    
    private static MCWebView _instance;
    
    public MCWebView(Activity activity, RelativeLayout parent) {
        _activity = activity;
        _parentView = parent;
        _isOpen = false;
        _instance = this;
    }
    
    public static void open(String url) {
        _instance.showWebView();
        _instance.openURL(url);
    }
    
    /**
     * webviewをフルスクリーンで表示(viewに追加をするのみ).
     */
    public void showWebView() {
        showWebView(_parentView.getLeft(), _parentView.getTop(), _parentView.getRight(), _parentView.getBottom());
    }
    
    /**
     * webviewの表示(viewに追加をするのみ).
     *
     * @param [in] x x座標.
     * @param [in] y y座標.
     * @param [in] width 横サイズ.
     * @param [in] height 縦サイズ.
     */
    public void showWebView(final int x, final int y, final int width, final int height) {
        if (_isOpen) return;
        _isOpen = true;
        
        _activity.runOnUiThread(new Runnable() {
            @SuppressLint("SetJavaScriptEnabled")
            @Override
            public void run() {
                _webView = new WebView(_activity);
                _parentView.addView(_webView);
                
                RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams)_webView.getLayoutParams();
                layoutParams.leftMargin = x;
                layoutParams.topMargin = y;
                layoutParams.width = width;
                layoutParams.height = height;
                _webView.setLayoutParams(layoutParams);                
                _webView.setBackgroundColor(Color.WHITE);
                
                _webView.getSettings().setAppCacheEnabled(false);
                _webView.getSettings().setJavaScriptEnabled(true);
                _webView.getSettings().setCacheMode(WebSettings.LOAD_NO_CACHE);
                _webView.getSettings().setBuiltInZoomControls(false);
                _webView.getSettings().setSupportZoom(false);
                //_webView.getSettings().setUserAgentString(DeviceInfo.getUserAgent());
                _webView.getSettings().setLoadWithOverviewMode(true);
                _webView.getSettings().setUseWideViewPort(true);
                
                _webView.setWebChromeClient(new WebChromeClient() {
                    @Override
                    public boolean onJsAlert(WebView view, String url, String message, android.webkit.JsResult result) {
                        return super.onJsAlert(view, url, message, result);
                    }           
                });
                    
                // ボタンをビューに追加
                addExitButton();
                
                // ブログレスバー
                _progressBar = new ProgressBar(_activity);
                RelativeLayout.LayoutParams progressBarLayout = new RelativeLayout.LayoutParams(PROGRESS_BAR_SIZE, PROGRESS_BAR_SIZE);
                progressBarLayout.leftMargin = x + width/2 - PROGRESS_BAR_SIZE/2;
                progressBarLayout.topMargin  = y + height/2 - PROGRESS_BAR_SIZE/2;
                _progressBar.setLayoutParams(progressBarLayout);
                _parentView.addView(_progressBar);                
                
                _webView.setWebViewClient(new WebViewClient(){
                     @Override // アクセス前処理
                     public boolean shouldOverrideUrlLoading(WebView view,String url){
                        final String closeWebViewString = "native://closeWebPage";
                        final String installCheck = "install://";

                        // リンク先URLによる動作
                        if (url.startsWith("webto")) { // 外部ブラウザを起動
                            url = url.replaceFirst("webto://", "http://");
                            MCLog.d("外部ブラウザ起動 : [" + url + "]");
                            Intent i = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
                            _activity.startActivity(i);
                            return true;
                        }
                        else if (url.startsWith(installCheck)) { // アプリのインストール存在確認
                            // install://[対象アプリのURLスキーム]
                            String packageName = url.substring( installCheck.length() );
                            
                            boolean installed = isInstalledApp(packageName);
                            String calljs = String.format("javascript:%s()", (installed ? "install": "notInstall"));
                            _webView.loadUrl(calljs);
                            return true;
                        }
                        else if (url.startsWith(closeWebViewString)) { // WebViewを閉じる
                            removeWebView();
                            return true;
                        }

                        // プログレスバーを表示する
                        _progressBar.setVisibility(ProgressBar.VISIBLE);
                        return super.shouldOverrideUrlLoading(view, url);
                     }
                     
                     @Override // 読み込み完了時
                     public void onPageFinished(WebView view , String url) {
                         // super.onPageFinished(view, url);
                         
                         // ページ読み込みが完了したら、プログレスバーを非表示にする
                         _progressBar.setVisibility(ProgressBar.GONE);
                     }
                });
            }
        });
    }
    
    /**
     * webviewを閉じるボタンを追加する.
     */
    private void addExitButton() {
        _exitButton = new ImageButton(_activity);
        
        Bitmap bitmap = BitmapFactory.decodeResource(_activity.getResources(), Res.getDrawableId(_activity, "webview_close_button_2x"));
        _exitButton.setImageBitmap(bitmap);
        
        // 背景色を透明に
        _exitButton.setBackgroundColor(Color.argb(0, 255, 255, 255));
        
        // ボタンのクリックリスナー
        _exitButton.setOnClickListener(new View.OnClickListener() {                    
            @Override
            public void onClick(View v) {
                // webviewをビューから下ろす
                removeWebView();
            }
        });

      RelativeLayout.LayoutParams param = new RelativeLayout.LayoutParams(bitmap.getWidth(), bitmap.getHeight());   
      _exitButton.setLayoutParams(param);     
       _parentView.addView(_exitButton);
    }
    
    /**
     * webview閉じるボタンの座標を設定する.
     *
     * @param [in] buttonImageName 表示するボタン画像
     * @param [in] x x座標.
     * @param [in] y y座標.
     */
    public void setExitButtonPosition(final int x, final int y) {
        if (_exitButton == null) return;

        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                RelativeLayout.LayoutParams param = (RelativeLayout.LayoutParams) _exitButton.getLayoutParams();
                param.leftMargin = x;
                param.topMargin = y;
                _exitButton.setLayoutParams( param );
            }
        });
    }
        
    private void openURL(final String url) {     
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                _webView.loadUrl(url);
            }
        });
    }
    
    /**
     * webviewを閉じる(viewから下ろす).
     */
    public void removeWebView() {
        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                _parentView.removeView(_webView);
                _webView.destroy();
                _webView = null;
                    
                _parentView.removeView(_exitButton);
                _parentView.removeView(_progressBar);
                
                _exitButton = null;
                _progressBar = null;
            }
        });
        
        _isOpen = false;
    }
    
    /**
     *  viewを開いているかどうか.
     *
     * @return viewを開いているか.
     */
    public static boolean isOpen() {
        return _instance._isOpen;
    }
    
    /**
     * アプリのインストール判定.
     *
     * @return アプリがインストールされているか.
     */
    public boolean isInstalledApp(String packageName) {
        Intent mainIntent = new Intent(Intent.ACTION_MAIN, null);  
        mainIntent.addCategory(Intent.CATEGORY_LAUNCHER);  
        // パッケージマネージャからインストール済みメインアプリリストを取得  
        List<ResolveInfo> apps = _activity.getPackageManager().queryIntentActivities(mainIntent, 0);  
        for (ResolveInfo info : apps) {  
            ActivityInfo activityInfo = info.activityInfo;
            // DLog.v("installed: [%s]", activityInfo.packageName); 
            if (activityInfo.packageName.equals(packageName)) {
                MCLog.v("found install app : [%s]", packageName);
                return true;
            }
        }
        return false;
    }
}

