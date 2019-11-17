//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_FFDEMUX_H
#define CUSTOMVIDEOPLAYER_FFDEMUX_H

#include "IDemux.h"
#include "XParameter.h"

struct AVFormatContext;

class FFDemux : public IDemux {

public:

    //重写父类方法
    //打开文件或者流媒体
    virtual bool open(const char *url);

    virtual void close();

    //获取视频参数
    virtual XParameter getVPara();

    //获取音频参数
    virtual XParameter getAPara();


    //读取一帧数据 数据由调用者清理
    virtual XData read();

    //构造函数
    FFDemux();

private:
    AVFormatContext *ic = nullptr;
    int audioStream = 1;
    int videoStream = 0;
    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_FFDEMUX_H
