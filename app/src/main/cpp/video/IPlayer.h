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

    IDemux *demux = 0;
    IDecode *vDecode = 0;
    IDecode *aDecode = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;


protected:
    //用作音视频同步
    void main();

    IPlayer() {};

    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_IPLAYER_H
