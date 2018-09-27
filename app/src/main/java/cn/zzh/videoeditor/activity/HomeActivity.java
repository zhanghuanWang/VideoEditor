package cn.zzh.videoeditor.activity;

import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.ImageView;

import cn.zzh.videoeditor.R;
import cn.zzh.videoeditor.util.Utils;

public class HomeActivity extends AppCompatActivity {

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
    }

    private void findViews() {
        mIvEditor = findViewById(R.id.home_iv_editor);
        mIvRecorder = findViewById(R.id.home_iv_recorder);
        mIvPlayer = findViewById(R.id.home_iv_player);
    }

    private void layoutViews() {
        int margin = (int) (getResources().getDimension(R.dimen.margin_normal));
        BitmapFactory.Options options = Utils.getImageInfo(R.drawable.img_editor);
        // 左右两边的间隔
        int width = Utils.getScreenWidth() - margin * 2;
        int height = width * options.outHeight / options.outWidth;
        mIvEditor.getLayoutParams().height = height;

        options = Utils.getImageInfo(R.drawable.img_recorder);
        // 左右两边和中间的间隔
        width = (Utils.getScreenWidth() - margin * 3) / 2;
        height = width * options.outHeight / options.outWidth;
        mIvRecorder.getLayoutParams().height = height;

        options = Utils.getImageInfo(R.drawable.img_player);
        height = width * options.outHeight / options.outWidth;
        mIvPlayer.getLayoutParams().height = height;
    }

}
