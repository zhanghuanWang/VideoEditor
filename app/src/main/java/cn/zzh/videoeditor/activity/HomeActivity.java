package cn.zzh.videoeditor.activity;

import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import cn.zzh.videoeditor.BaseActivity;
import cn.zzh.videoeditor.R;
import cn.zzh.videoeditor.util.Utils;

public class HomeActivity extends BaseActivity implements View.OnClickListener {

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

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.home_iv_recorder:
                startActivity(RecordActivity.class);
                break;
        }
    }

}
