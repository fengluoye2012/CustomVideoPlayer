#include <jni.h>
#include <string>
#include "XThread.h"

#include "native-lib.h"
#include "FFDemux.h"
#include "LogUtils.h"
#include "FFDecode.h"
#include <android/native_window_jni.h>
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"

using namespace std;
using std::string;

IVideoView *view = nullptr;


jstring native_stringFromJNI(JNIEnv *env, jobject obj) {
    string hello = "Hello from C++";

    LOGI(TAG, "native_stringFromJNI");

    IDemux *de = new FFDemux();
    //de->open("/sdcard/v1080.mp4");

    IDecode *vdecode = new FFDecode();
    //vdecode->open(de->getVPara());

    IDecode *adevode = new FFDecode();
    //adevode->open(de->getAPara());

    de->addObs(vdecode);
    de->addObs(adevode);

    view = new GLVideoView();
    vdecode->addObs(view);

    IResample *resample = new FFResample();
    adevode->addObs(resample);

    IAudioPlay *audioPlay = new SLAudioPlay();
    resample->addObs(audioPlay);


    IPlayer::get()->demux = de;
    IPlayer::get()->aDecode = adevode;
    IPlayer::get()->videoView = view;

    IPlayer::get()->resample = resample;
    IPlayer::get()->audioPlay = audioPlay;

    IPlayer::get()->open("/sdcard/v1080.mp4");
    IPlayer::get()->start();


    de->start();
    vdecode->start();
    adevode->start();


    return env->NewStringUTF(hello.c_str());
}

void native_initView(JNIEnv *env, jobject obj, jobject surface) {
    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    view->setRender(win);
    IPlayer::get()->initView(win);
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
    JNIEnv *env = nullptr;
    jint result = JNI_FALSE;

    //获取env指针；
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }

    if (env == nullptr) {
        return result;
    }

    //native方法注册
    registerNative(env);

    //初始化硬解码
    FFDecode::initHard(jvm);
    result = JNI_VERSION_1_6;
    return result;
}
