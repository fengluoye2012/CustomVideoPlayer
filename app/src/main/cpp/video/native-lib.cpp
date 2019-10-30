#include <jni.h>
#include <string>

#include "native-lib.h"

using namespace std;
using std::string;


jstring native_stringFromJNI(JNIEnv *env, jobject obj) {
    string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
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
        {"getString", "()Ljava/lang/String;", (void *) native_stringFromJNI},
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

jint  JNICALL JNI_OnLoad(JavaVM *jvm, void *resetved) {
    JNIEnv *env = NULL;
    jint result = JNI_FALSE;

    //获取env指针
    if (jvm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_TRUE) {
        return result;
    }

    if (env == NULL) {
        return result;
    }

    //native方法注册
    registerNative(env);


    result = JNI_VERSION_1_6;
    return result;
}
