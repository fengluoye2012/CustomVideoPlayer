//
// Created by wjw on 2019-10-30.
//

#ifndef CUSTOMVIDEOPLAYER_NATIVE_LIB_H
#define CUSTOMVIDEOPLAYER_NATIVE_LIB_H

#include <jni.h>

#define TAG "XPlay"


jstring native_stringFromJNI(JNIEnv *env, jobject obj);

void native_initView(JNIEnv *env,jobject obj,jobject surface);

jint registerNative(JNIEnv *env);

void initFFmpeg(JavaVM *jvm);


#endif //CUSTOMVIDEOPLAYER_NATIVE_LIB_H
