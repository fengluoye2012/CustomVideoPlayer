//
// Created by wjw on 2019-10-30.
//

#ifndef CUSTOMVIDEOPLAYER_NATIVE_LIB_H
#define CUSTOMVIDEOPLAYER_NATIVE_LIB_H

#include <jni.h>

jstring native_stringFromJNI(JNIEnv *env, jobject obj);

jint registerNative(JNIEnv *env);


#endif //CUSTOMVIDEOPLAYER_NATIVE_LIB_H
