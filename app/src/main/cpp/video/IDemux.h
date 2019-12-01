//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_IDEMUX_H
#define CUSTOMVIDEOPLAYER_IDEMUX_H

#include "IObserver.h"
#include "XData.h"
#include "XParameter.h"

//解封装接口
class IDemux : public IObserver {
public:
    //打开文件，或者流媒体 rmtp http rtsp
    virtual bool open(const char *url) = 0;
    virtual void close() = 0;
    //获取视频参数
    virtual XParameter getVPara() = 0;

    //获取音频参数
    virtual XParameter getAPara() = 0;

    //读取一帧数据，数据由调用者清理
    virtual XData read() = 0;

    //总时长（毫秒）
    int totalMs = 0;
protected:
    virtual void main();

};

#endif //CUSTOMVIDEOPLAYER_IDEMUX_H
