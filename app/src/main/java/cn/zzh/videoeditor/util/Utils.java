package cn.zzh.videoeditor.util;


import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.util.DisplayMetrics;

import java.io.File;

import cn.zzh.videoeditor.BaseApplication;
import cn.zzh.videoeditor.R;

@SuppressWarnings("unused")
public final class Utils {

    private static final String SDCARD = Environment.getExternalStorageDirectory().getAbsolutePath();
    private static final String APP_DIR = SDCARD + "/AVGraphics";

    @SuppressLint("StaticFieldLeak")
    private static Context sContext = BaseApplication.getContext();
    private static Handler sHandler = new Handler(Looper.getMainLooper());

    static {
        createDir(APP_DIR);
    }

    private Utils() {
    }

    private static void createDir(String path) {
        File file = new File(path);
        if (!file.exists() && !file.mkdir()) {
            ToastHelper.show(getString(R.string.msg_create_folder_error) + ": " + path);
        }
    }

    public static String getString(int id) {
        return sContext.getString(id);
    }

    public static String getAppDir() {
        return APP_DIR;
    }

    public static void runOnUiThread(Runnable action) {
        if (Looper.myLooper() == Looper.getMainLooper()) {
            action.run();
        } else {
            sHandler.post(action);
        }
    }

    public static int getScreenWidth() {
        DisplayMetrics metrics = sContext.getResources().getDisplayMetrics();
        return metrics.widthPixels;
    }

    public static int getScreenHeight() {
        DisplayMetrics metrics = sContext.getResources().getDisplayMetrics();
        return metrics.heightPixels;
    }

    public static int dp2px(int dp) {
        return (int)(sContext.getResources().getDisplayMetrics().density * dp);
    }

    public static BitmapFactory.Options getImageInfo(int id) {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeResource(sContext.getResources(), id, options);
        options.inJustDecodeBounds = false;
        return options;
    }

}
