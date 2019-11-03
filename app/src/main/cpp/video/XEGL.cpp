//
// Created by wjw on 2019-11-03.
//

#include <android/native_window.h>
#include <EGL/egl.h>
#include "XEGL.h"
#include "LogUtils.h"
#include "native-lib.h"

class CXEGL : public XEGL {

public:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    virtual void draw() {
        if (display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE) {
            return;
        }

        eglSwapBuffers(display, surface);
    }

    virtual bool init(void *win) {
        auto *nwin = (ANativeWindow *) win;

        //初始化EGL
        //1 获取EGLDisplay对象 显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY) {
            LOGE(TAG, "eglGetDisplay failed");
            return false;
        }
        LOGE(TAG, "eglGetDisplay success");

        //2 初始化DisPlay
        if (EGL_TRUE != eglInitialize(display, nullptr, nullptr)) {
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
            LOGE(TAG, "eglChooseConfig failed");
            return false;
        }
        LOGE(TAG, "eglChooseConfig success");

        surface = eglCreateWindowSurface(display, config, nwin, nullptr);

        //4 打开并创建EGL上下文
        const EGLint ctxAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);

        if (context == EGL_NO_CONTEXT) {
            LOGE(TAG, "eglCreateContext failed");
            return false;
        }
        LOGE(TAG, "eglCreateContext success");

        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            LOGE(TAG, "eglMakeCurrent failed");
            return false;
        }
        LOGE(TAG, "eglMakeCurrent success");
        return true;
    }

};;

XEGL *XEGL::get() {
    static CXEGL egl;
    return &egl;
}
