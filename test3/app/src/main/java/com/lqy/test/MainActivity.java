package com.lqy.test;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    NDKHelper helper = new NDKHelper();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.tv);

        new Thread(new Runnable() {
            @Override
            public void run() {
                helper.convert(
                        Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "777.mp4",
                        Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator + "777.ts"
                );
            }
        }).start();
    }
}
