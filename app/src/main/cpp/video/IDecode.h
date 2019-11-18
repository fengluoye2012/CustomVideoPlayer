//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_IDECODE_H
#define CUSTOMVIDEOPLAYER_IDECODE_H


#include "IObserver.h"
#include "XParameter.h"
#include "XData.h"
#include <list>


//解码接口 支持硬解码
class IDecode : public IObserver {
public:
    //打开解码器
    virtual bool open(XParameter para, bool isHard = false) = 0;

    virtual void close() = 0;

    //future模型 发送数据到线程解码
    virtual bool sendPacket(XData pkt) = 0;

    //从线程中获取解码结果  再次调用会复用上次空间，线程不安全
    virtual XData recvFrame() = 0;

    //由主体notify的数据 阻塞
    virtual void update(XData pkt);

    bool isAudio = false;

    //最大的队列缓冲
    int maxList = 100;

    //同步时间，再次打开文件要清理
    int synPts = 0;
    int pts = 0;

protected:
    virtual void main();

    //读取缓冲
    std::list<XData> packs;
    std::mutex packsMutex;


};


#endif //CUSTOMVIDEOPLAYER_IDECODE_H
