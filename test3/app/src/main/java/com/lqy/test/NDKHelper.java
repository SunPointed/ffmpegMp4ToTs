package com.lqy.test;

/**
 * Created by lqy on 2018/5/11.
 */

public class NDKHelper {
    static {
        System.loadLibrary("avcodec");
        System.loadLibrary("avdevice");
        System.loadLibrary("avfilter");
        System.loadLibrary("avformat");
        System.loadLibrary("avutil");
        System.loadLibrary("swresample");
        System.loadLibrary("swscale");
        System.loadLibrary("ndkhelper");
    }

    public native int convert(String mp4, String ts);
}
