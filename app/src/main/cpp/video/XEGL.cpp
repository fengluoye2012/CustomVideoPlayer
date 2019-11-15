//
// Created by wjw on 2019-11-03.
//

#include <android/native_window.h>
#include <EGL/egl.h>
#include <mutex>
#include "XEGL.h"
#include "LogUtils.h"
#include "native-lib.h"

class CXEGL : public XEGL {

public:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;
    std::mutex mux;

    virtual void draw() override {
        mux.lock();
        if (display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE) {
            mux.unlock();
            return;
        }

        eglSwapBuffers(display, surface);
        mux.unlock();
    }

    virtual void close() override {
        mux.lock();
        if (display == EGL_NO_DISPLAY) {
            mux.unlock();
            return;
        }

        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

        if (surface != EGL_NO_SURFACE) {
            eglDestroySurface(display, surface);
        }

        if (surface != EGL_NO_CONTEXT) {
            eglDestroyContext(display, context);
        }

        eglTerminate(display);

        display = EGL_NO_DISPLAY;
        surface = EGL_NO_SURFACE;
        context = EGL_NO_CONTEXT;
        mux.unlock();
    }

    virtual bool init(void *win) override {
        ANativeWindow *nwin = (ANativeWindow *) win;

        close();
        mux.lock();

        //初始化EGL
        //1 获取EGLDisplay对象 显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY) {
            mux.unlock();
            LOGE(TAG, "eglGetDisplay failed");
            return false;
        }
        LOGE(TAG, "eglGetDisplay success");

        //2 初始化DisPlay
        if (EGL_TRUE != eglInitialize(display, nullptr, nullptr)) {
            mux.unlock();
            LOGE(TAG, "eglInitialize failed");
            return false;
        }
        LOGE(TAG, "eglInitialize success");

        //3 获取配置并创建surface
        EGLint configSpec[] = {
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_NONE
        };

        EGLConfig config = nullptr;
        EGLint numConfigs = 0;
        if (EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &numConfigs)) {
            mux.unlock();
            LOGE(TAG, "eglChooseConfig failed");
            return false;
        }
        LOGE(TAG, "eglChooseConfig success");

        surface = eglCreateWindowSurface(display, config, nwin, nullptr);

        //4 打开并创建EGL上下文
        const EGLint ctxAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);

        if (context == EGL_NO_CONTEXT) {
            mux.unlock();
            LOGE(TAG, "eglCreateContext failed");
            return false;
        }
        LOGE(TAG, "eglCreateContext success");

        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            mux.unlock();
            LOGE(TAG, "eglMakeCurrent failed");
            return false;
        }
        LOGE(TAG, "eglMakeCurrent success");
        mux.unlock();
        return true;
    }

};;

XEGL *XEGL::get() {
    static CXEGL egl;
    return &egl;
}
