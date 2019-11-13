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
    virtual bool open(const char *url) override;

    void close() override;

    //获取视频参数
    virtual XParameter getVPara() override;

    //获取音频参数
    virtual XParameter getAPara() override;


    //读取一帧数据 数据由调用者清理
    virtual Data read() override;

    //构造函数
    FFDemux();

private:
    AVFormatContext *ic = nullptr;
    int audioStream = -1;
    int videoStream = -1;
    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_FFDEMUX_H
