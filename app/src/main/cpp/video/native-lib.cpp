#include <jni.h>
#include <string>

#include "native-lib.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include <android/native_window_jni.h>
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"
#include "IPlayerProxy.h"
#include "LogUtils.h"

using namespace std;
using std::string;

jstring native_stringFromJNI(JNIEnv *env, jobject obj) {
    string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

void native_initView(JNIEnv *env, jobject obj, jobject surface) {
    initFFmpeg();
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayerProxy::get()->initView(win);
}

/**
 * 动态注册，每增加一个native方法，需要在数组中增加一个JNINativeMethod结构体；
 * JNINativeMethod 是结构体
 *
 * const char* name; Java 中的函数名
 * const char* signature; Java函数签名，格式为(输入参数类型)返回值类型
 * void* fnPtr; native函数名
 */
static JNINativeMethod gMethods[] = {
        {"getString", "()Ljava/lang/String;",      (void *) native_stringFromJNI},
        {"initView",  "(Landroid/view/Surface;)V", (void *) native_initView}
};


//System.loadLibrary过程会自动调用JNI_OnLoad,在此动态注册；
jint registerNative(JNIEnv *env) {
    jclass cls = env->FindClass("com/test/customvideoplayer/MediaPlayer");
    if (cls == nullptr) {
        return JNI_FALSE;
    }

    /**
     * 注册
    * jclass clazz:
    * const JNINativeMethod* methods: JNINativeMethod指针
    * jint nMethods:方法个数
    */
    jint code = env->RegisterNatives(cls, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
    if (code < 0) {
        return JNI_FALSE;
    }
    return JNI_OK;
}


jint  JNICALL JNI_OnLoad(JavaVM *jvm, void *res) {
    mJvm = jvm;
    JNIEnv *env = 0;
    jint result = JNI_FALSE;

    //获取env指针；
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }

    if (!env) {
        return result;
    }

    //native方法注册
    registerNative(env);

    result = JNI_VERSION_1_6;
    return result;
}

void initFFmpeg() {

    //初始化硬解码
    IPlayerProxy::get()->init();

    IPlayerProxy::get()->open("/sdcard/v1080.mp4");
//    IPlayerProxy::get()->open(
//            "http://dev.cdlianmeng.com/Fm4KJMvctkjfK6LJBB5o1MS0fQV1?sign=7a72a39428ff8ce0b74f288c1fa61091&t=5dcf679e");
    IPlayerProxy::get()->start();


}
