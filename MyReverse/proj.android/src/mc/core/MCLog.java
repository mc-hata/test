package mc.core;

import mc.debug.Debug;
import android.util.Log;

/**
 * ログ出力ヘルパークラス
 * Android SDK の Log クラスのラッパー
 * 
 * @author nkobayashi
 */
public class MCLog {
    private static final String TAG = "mc-java";
    
    private static boolean _isMethodInfoEnabled = false;
    
    /**
     * ログ出力時に、ファイル名、メソッド名、行番号を表示するかを設定します。
     * 注意:
     * - パフォーマンスに影響がでる場合があります。
     * - 内部クラスからのログ出力は、正しい情報を出力できない場合があります。
     * 
     * @param enabled
     */
    public static void setMethodInfoEnabled(boolean enabled) {
        _isMethodInfoEnabled = enabled;
    }
    
    // コールスタックの深さに依存するので、場合によっては正しくメソッド情報が取得できない場合がある。
    private static String getMethodInfo() {
        if (!_isMethodInfoEnabled) return "";
        
        // StackTraceElement[] elts = Thread.currentThread().getStackTrace();
        StackTraceElement e = Thread.currentThread().getStackTrace()[4]; // 4 はスタ目的のメソッドコール位置を指す。コールスタックに依存

        StringBuffer buf = new StringBuffer();
        buf.append('[');
        buf.append(e.getFileName());
        buf.append('#');
        buf.append(e.getMethodName());
        buf.append(':');
        buf.append(e.getLineNumber());
        buf.append("] ");
        return buf.toString();
    }

    public static void v(String format, Object... args) {
        if (Debug.LOG) {
            Log.v(TAG, getMethodInfo() + String.format(format, args));
        }
    }
    
    public static void d(String format, Object... args) {
        if (Debug.LOG) {
            Log.d(TAG, getMethodInfo() + String.format(format, args));
        }
    }
    
    public static void i(String format, Object... args) {
        if (Debug.LOG) {
            Log.i(TAG, getMethodInfo() + String.format(format,  args));
        }
    }
    
    public static void w(String format, Object... args) {
        if (Debug.LOG) {
            Log.w(TAG, getMethodInfo() + String.format(format,  args));
        }
    }
    
    public static void e(String format, Object... args) {
        if (Debug.LOG) {
            Log.e(TAG, getMethodInfo() + String.format(format, args));
        }
    }
    
    public static void vWithTag(String tag, String format, Object... args) {
        if (Debug.LOG) {
            Log.v(tag, getMethodInfo() + String.format(format, args));
        }
    }
    
    public static void dWithTag(String tag, String format, Object... args) {
        if (Debug.LOG) {
            Log.d(tag, getMethodInfo() + String.format(format,  args));
        }
    }
    
    public static void iWithTag(String tag, String format, Object... args) {
        if (Debug.LOG) {
            Log.i(tag, getMethodInfo() + String.format(format,  args));
        }
    }
    
    public static void wWithTag(String tag, String format, Object... args) {
        if (Debug.LOG) {
            Log.w(tag, getMethodInfo() + String.format(format, args));
        }
    }
    
    public static void eWithTag(String tag, String format, Object... args) {
        if (Debug.LOG) {
            Log.e(tag, getMethodInfo() + String.format(format, args));
        }
    }
}
