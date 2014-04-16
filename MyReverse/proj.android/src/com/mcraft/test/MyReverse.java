/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.mcraft.test;
import mc.bridge.Bridge;
import mc.core.Settings;
import mc.iab.InAppBillingHelper;
import mc.ui.MCWebView;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Vibrator;
import android.widget.RelativeLayout;

public class MyReverse extends Cocos2dxActivity {
    private RelativeLayout _webViewLayout;
    private MCWebView _webView;
    
    private InAppBillingHelper _iabHelper;
    
    private static Activity m_activity;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        _webViewLayout = new RelativeLayout(this);
        addContentView(_webViewLayout, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.FILL_PARENT, RelativeLayout.LayoutParams.FILL_PARENT));
	
        _webView = new MCWebView(this, _webViewLayout);
        if (Settings.IN_APP_BILLING_ENABLED) {
            _iabHelper = new InAppBillingHelper(this);
        }
        Bridge.init(this, _iabHelper);
        
        m_activity = this;
    }
    
    @Override
    protected void onDestroy() {
        super.onDestroy();
        
        if (_iabHelper != null) {
            _iabHelper.dispose();
        }
        _iabHelper = null;
    }

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
        // MyReverse should create stencil buffer
        glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

        return glSurfaceView;
    }
    
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == InAppBillingHelper.IN_APP_BILLING_REQUEST_CODE) {
            if (_iabHelper.handleActivityResult(requestCode, resultCode, data)) {
                
            }
        }
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }
    
    public static void func1()
    {
    	Vibrator vib = (Vibrator)m_activity.getSystemService(Context.VIBRATOR_SERVICE);
    	vib.vibrate(100);
    }
}

