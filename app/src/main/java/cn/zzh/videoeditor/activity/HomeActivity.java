package cn.zzh.videoeditor.activity;

import android.Manifest;
import android.content.pm.PackageManager;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.view.View;
import android.widget.ImageView;

import java.util.ArrayList;
import java.util.List;

import cn.zzh.videoeditor.BaseActivity;
import cn.zzh.videoeditor.R;
import cn.zzh.videoeditor.util.ToastHelper;
import cn.zzh.videoeditor.util.Utils;

public class HomeActivity extends BaseActivity implements View.OnClickListener {

    private static final int RC_PERMISSION = 1;

    private ImageView mIvEditor;
    private ImageView mIvRecorder;
    private ImageView mIvPlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        init();
    }

    private void init() {
        findViews();
        layoutViews();
        setListener();
        requestPermissions();
    }

    private void findViews() {
        mIvEditor = findViewById(R.id.home_iv_editor);
        mIvRecorder = findViewById(R.id.home_iv_recorder);
        mIvPlayer = findViewById(R.id.home_iv_player);
    }

    private void layoutViews() {
        int margin = (int) (getResources().getDimension(R.dimen.margin_normal));
        BitmapFactory.Options options = Utils.getImageInfo(R.drawable.img_editor_normal);
        // 左右两边的间隔
        int width = Utils.getScreenWidth() - margin * 2;
        int height = width * options.outHeight / options.outWidth;
        mIvEditor.getLayoutParams().height = height;

        options = Utils.getImageInfo(R.drawable.img_recorder_normal);
        // 左右两边和中间的间隔
        width = (Utils.getScreenWidth() - margin * 3) / 2;
        height = width * options.outHeight / options.outWidth;
        mIvRecorder.getLayoutParams().height = height;

        options = Utils.getImageInfo(R.drawable.img_player_normal);
        height = width * options.outHeight / options.outWidth;
        mIvPlayer.getLayoutParams().height = height;
    }

    private void setListener() {
        mIvRecorder.setOnClickListener(this);
    }

    private void requestPermissions() {
        String[] permissions = {
                Manifest.permission.CAMERA,
                Manifest.permission.RECORD_AUDIO,
                Manifest.permission.MODIFY_AUDIO_SETTINGS,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.READ_EXTERNAL_STORAGE
        };
        List<String> list = new ArrayList<>();
        for (String permission : permissions) {
            if (ContextCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED) {
                list.add(permission);
            }
        }
        String[] requestArrays = new String[list.size()];
        for (int i = 0; i < list.size(); ++i) {
            requestArrays[i] = list.get(i);
        }
        if (requestArrays.length > 0) {
            ActivityCompat.requestPermissions(this, permissions, RC_PERMISSION);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        boolean granted = true;
        for (int grantResult : grantResults) {
            if (grantResult != PackageManager.PERMISSION_GRANTED) {
                granted = false;
            }
        }
        if (!granted) {
            ToastHelper.show(R.string.msg_no_permission);
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.home_iv_recorder:
                startActivity(RecordActivity.class);
                break;
        }
    }

}
