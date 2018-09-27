package cn.zzh.videoeditor.activity;

import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.SeekBar;

import cn.zzh.videoeditor.BaseActivity;
import cn.zzh.videoeditor.R;
import cn.zzh.videoeditor.view.CameraView;

public class RecordActivity extends BaseActivity {

    private CameraView mCameraView;
    private LinearLayout mLlControlBar;
    private SeekBar mSbBeauty;
    private SeekBar mSbSaturate;
    private SeekBar mSbBright;
    private Button mBtnSwitch;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_record);
        init();
    }

    private void init() {
        findViews();
        setListener();
        mCameraView.start();
    }

    private void findViews() {
        mLlControlBar = findViewById(R.id.record_ll_control_bar);
        mCameraView = findViewById(R.id.record_cv_preview);
        mSbBeauty = findViewById(R.id.record_sb_beauty);
        mSbSaturate = findViewById(R.id.record_sb_saturate);
        mSbBright = findViewById(R.id.record_sb_bright);
        mBtnSwitch = findViewById(R.id.record_btn_switch);
    }

    private void setListener() {
        mSbBeauty.setOnSeekBarChangeListener((DefaultSeekBarChangeListener) progress ->
                mCameraView.setBeautyLevel(progress));
        mSbSaturate.setOnSeekBarChangeListener((DefaultSeekBarChangeListener) progress ->
                mCameraView.setSaturateLevel(progress));
        mSbBright.setOnSeekBarChangeListener((DefaultSeekBarChangeListener) progress ->
                mCameraView.setBrightLevel(progress));

        mBtnSwitch.setOnClickListener(v -> {
            mCameraView.switchCamera();
            mLlControlBar.setVisibility(mCameraView.isFacingBack() ? View.GONE : View.VISIBLE);
        });
    }

    @Override
    protected void onPause() {
        super.onPause();
        mCameraView.release();
    }

    private interface DefaultSeekBarChangeListener extends SeekBar.OnSeekBarChangeListener {

        void onProgressChanged(float progress);

        @Override
        default void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            onProgressChanged(1.0f * progress / 100);
        }

        @Override
        default void onStartTrackingTouch(SeekBar seekBar) {

        }

        @Override
        default void onStopTrackingTouch(SeekBar seekBar) {

        }
    }

    static {
        System.loadLibrary("gles");
    }

}
