package com.ndk.lqy.ndk;

/**
 * Created by lqy on 2018/5/11.
 */

public class NDKHelper {
    static {
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avdevice-57");
        System.loadLibrary("avfilter-6");
        System.loadLibrary("avformat-57");
        System.loadLibrary("avutil-55");
        System.loadLibrary("swresample-2");
        System.loadLibrary("swscale-4");
        System.loadLibrary("ndkhelper");
    }

    private native int ffmpeg_h264(int codecID);

    public int test_h246(int id){
        return ffmpeg_h264(id);
    }
}
