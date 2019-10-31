//
// Created by wjw on 2019-10-30.
//

#ifndef CUSTOMVIDEOPLAYER_LOGUTILS_H
#define CUSTOMVIDEOPLAYER_LOGUTILS_H

class LogUtils {

};

#ifdef ANDROID

#include <android/log.h>

#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define LOGI(TAG,...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGE(TAG...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

#else

#define LOGD(...) printf("XPlay",__VA_ARGS__)
#define LOGI(...) printf("XPlay",__VA_ARGS__)
#define LOGE(...) printf("XPlay",__VA_ARGS__)

#endif

#endif //CUSTOMVIDEOPLAYER_LOGUTILS_H



