package cn.zzh.videoeditor;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;


public abstract class BaseActivity extends AppCompatActivity {

    protected final String TAG = this.getClass().getSimpleName();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(TAG, "--> onCreate");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG, "--> onResume");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.d(TAG, "--> onDestroy");
    }

    protected <T extends Activity> void startActivity(Class<T> clz) {
        Intent intent = new Intent(this, clz);
        startActivity(intent);
    }

}
