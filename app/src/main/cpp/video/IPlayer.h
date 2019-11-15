//
// Created by wjw on 2019-11-12.
//

#ifndef CUSTOMVIDEOPLAYER_IPLAYER_H
#define CUSTOMVIDEOPLAYER_IPLAYER_H


#include <mutex>
#include "XThread.h"
#include "XParameter.h"

class IDemux;

class IDecode;

class IVideoView;

class IAudioPlay;

class IResample;


class IPlayer : public XThread {

public:
    static IPlayer *get(unsigned char index = 0);

    virtual bool open(const char *path);

    virtual bool start();

    virtual void initView(void *win);

    //是否视频硬解码
    bool isHardDecode = false;

    //音频输出参数配置
    XParameter outPara;

    IDemux *demux = nullptr;
    IDecode *vDecode = nullptr;
    IDecode *aDecode = nullptr;
    IResample *resample = nullptr;
    IVideoView *videoView = nullptr;
    IAudioPlay *audioPlay = nullptr;


protected:
    //用作音视频同步
    void main() override;

    IPlayer() {};

    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_IPLAYER_H
