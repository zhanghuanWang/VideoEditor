package cn.zzh.videoeditor.util;


import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.widget.Toast;

import cn.zzh.videoeditor.BaseApplication;


@SuppressWarnings("unused")
public final class ToastHelper {


    @SuppressLint("StaticFieldLeak")
    private static Context sContext = BaseApplication.getContext();
    private static Handler sHandler = new Handler(Looper.getMainLooper());

    private ToastHelper() {
    }

    public static void show(String msg) {
        Toast.makeText(sContext, msg, Toast.LENGTH_SHORT).show();
    }

    public static void show(int stringId) {
        Toast.makeText(sContext, sContext.getString(stringId), Toast.LENGTH_SHORT).show();
    }

    public static void show(Context context, String msg) {
        Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
    }

    public static void show(Context context, int stringId) {
        Toast.makeText(context, context.getString(stringId), Toast.LENGTH_SHORT).show();
    }

    public static void showLong(String msg) {
        Toast.makeText(sContext, msg, Toast.LENGTH_LONG).show();
    }

    public static void showLong(int stringId) {
        Toast.makeText(sContext, sContext.getString(stringId), Toast.LENGTH_LONG).show();
    }

    public static void showLong(Context context, String msg) {
        Toast.makeText(context, msg, Toast.LENGTH_LONG).show();
    }

    public static void showLong(Context context, int stringId) {
        Toast.makeText(context, context.getString(stringId), Toast.LENGTH_LONG).show();
    }

    public static void showOnUiThread(final String msg) {
        if (Looper.myLooper() != Looper.getMainLooper()) {
            sHandler.post(() -> Toast.makeText(sContext, msg, Toast.LENGTH_SHORT).show());
        } else {
            show(msg);
        }
    }

    public static void showOnUiThread(final int stringId) {
        if (Looper.myLooper() != Looper.getMainLooper()) {
            sHandler.post(() ->
                    Toast.makeText(sContext, sContext.getString(stringId), Toast.LENGTH_SHORT).show());
        } else {
            show(stringId);
        }
    }

    public static void showOnUiThread(final Activity activity, final String msg) {
        activity.runOnUiThread(() -> Toast.makeText(activity, msg, Toast.LENGTH_SHORT).show());
    }

    public static void showOnUiThread(final Activity activity, final int stringId) {
        activity.runOnUiThread(() ->
                Toast.makeText(activity, activity.getString(stringId), Toast.LENGTH_SHORT).show());
    }

}
