package com.test.customvideoplayer;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class CustomMediaView extends GLSurfaceView implements SurfaceHolder.Callback, GLSurfaceView.Renderer {


    public CustomMediaView(Context context) {
        this(context, null);
    }

    public CustomMediaView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }


    @Override
    public void surfaceCreated(SurfaceHolder holder) {

        //初始化opengl egl 显示
        MediaPlayer.initView(holder.getSurface());

        //android 8.0 需要设置
        setRenderer(this);

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

    }

    @Override
    public void onDrawFrame(GL10 gl) {

    }
}
