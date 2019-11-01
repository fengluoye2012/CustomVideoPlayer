//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_IDEMUX_H
#define CUSTOMVIDEOPLAYER_IDEMUX_H

#include "IObserver.h"
#include "Data.h"
#include "XParameter.h"

//解封装接口
class IDemux : public IObserver {

public:

    //纯虚函数  打开文件或者流媒体
    virtual bool open(const char *url) = 0;

    //获取视频参数
    virtual XParameter getVPara()=0;

    //获取音频参数
    virtual XParameter getAPara()=0;

    //读取一帧数据，数据由调用者清理
    virtual Data read() = 0;

    //总时长（毫秒）
    int totalMs = 0;

protected:
    virtual void main();
};


#endif //CUSTOMVIDEOPLAYER_IDEMUX_H
