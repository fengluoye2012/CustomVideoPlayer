package com.test.customvideoplayer;


public class MediaPlayer {

    static {
        System.loadLibrary("native-lib");
    }

    public static native String getString();


}
