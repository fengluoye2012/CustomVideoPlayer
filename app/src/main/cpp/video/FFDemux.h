//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_FFDEMUX_H
#define CUSTOMVIDEOPLAYER_FFDEMUX_H

#include "IDemux.h"

struct AVFormatContext;

// 使用宏定义 定义TAG 避免使用全局变量；
#define TAG "FFDemux"

class FFDemux : public IDemux {

public:

    //重写父类方法
    //打开文件或者流媒体
    virtual bool open(const char *url);

    //读取一帧数据 数据由调用者清理
    virtual Data read();

    //构造函数
    FFDemux();

private:
    AVFormatContext *ic = nullptr;
};


#endif //CUSTOMVIDEOPLAYER_FFDEMUX_H
