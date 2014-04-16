package mc.debug;

public class Debug {
    /**
     * 全てのデバッグフラグを制御するフラグ
     * このフラグをオフにすると、全てのデバッグフラグがオフになります。
     */
    private static final boolean VALIDITY_DEBUG = true;
    
    /**
     * 外部公開用のデバッグフラグ
     */
    public static final boolean ON = VALIDITY_DEBUG;
    
    /**
     * ログ出力
     */
    public static final boolean LOG = VALIDITY_DEBUG && true;
}
