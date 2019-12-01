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

    //打开文件，或者流媒体 rmtp http rtsp
    virtual bool open(const char *url);

    virtual void close();

    //获取视频参数
    virtual XParameter getVPara();

    //获取音频参数
    virtual XParameter getAPara();

    //读取一帧数据，数据由调用者清理
    virtual XData read();

    FFDemux();

private:
    AVFormatContext *ic = 0;
    std::mutex mux;
    int audioStream = 1;
    int videoStream = 0;
};

#endif //CUSTOMVIDEOPLAYER_FFDEMUX_H
