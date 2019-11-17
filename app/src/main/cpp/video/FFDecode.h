//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_FFDECODE_H
#define CUSTOMVIDEOPLAYER_FFDECODE_H

#include "IDecode.h"
#include "XParameter.h"
#include "XData.h"


struct AVCodecContext;
struct AVFrame;
class FFDecode:public IDecode
{
public:
    static void initHard(void *vm);

    virtual bool open(XParameter para,bool isHard=false);
    virtual void close();
    //future模型 发送数据到线程解码
    virtual bool sendPacket(XData pkt);

    //从线程中获取解码结果，再次调用会复用上次空间，线程不安全
    virtual XData recvFrame();

protected:
    AVCodecContext *codec = 0;
    AVFrame *frame = 0;
    std::mutex mux;
};



#endif //CUSTOMVIDEOPLAYER_FFDECODE_H
