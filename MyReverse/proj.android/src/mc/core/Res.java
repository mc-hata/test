package mc.core;

import android.content.Context;

public class Res {
    private static int getIdentifier(Context context, String type, String name) {
        return context.getResources().getIdentifier(name, type, context.getPackageName());
    }
    
    public static int getLayoutId(Context context, String name) {
        return getIdentifier(context, "layout", name);
    }
    
    public static int getStringId(Context context, String name) {
        return getIdentifier(context, "string", name);
    }
    
    public static int getDrawableId(Context context, String name) {
        return getIdentifier(context, "drawable", name);
    }
    
    public static int getRawId(Context context, String name) {
        return getIdentifier(context, "raw", name);
    }
    
    public static int getId(Context context, String name) {
        return getIdentifier(context, "id", name);
    }
    
    public static String getString(Context context, String name) {
        int id = getStringId(context, name);
        return context.getResources().getString(id);       
    }
}
