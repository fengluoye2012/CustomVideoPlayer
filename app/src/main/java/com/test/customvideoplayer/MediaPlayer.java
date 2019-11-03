package com.test.customvideoplayer;


import android.view.Surface;

public class MediaPlayer {

    static {
        System.loadLibrary("native-lib");
    }

    public static native String getString();

    public static native void initView(Surface surface);


}
