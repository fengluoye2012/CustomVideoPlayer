//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_IDECODE_H
#define CUSTOMVIDEOPLAYER_IDECODE_H


#include "IObserver.h"
#include "XParameter.h"
#include "Data.h"
#include <list>


//解码接口 支持硬解码
class IDecode : public IObserver {

public:

    //打开解码器
    virtual bool open(XParameter para, bool isHard = false) = 0;

    virtual void close() = 0;

    //future 模型 发送数据到线程解码
    virtual bool sendPacket(Data pkt) = 0;

    //从线程中获取编解码结果 再次调用会复用上次空间，线程不安全；
    virtual Data recvFrame() = 0;

    //由主体notify的数据 阻塞
    virtual void update(Data pkt) override ;

    bool isAudio = false;

    //最大的队列缓存
    int maxList = 100;

    //同步时间，再次打开文件要清理
    int synPts = 0;
    int pts = 0;

protected:
    virtual void main() override;

    //读取缓存
    std::list<Data> packs;
    std::mutex packMutex;
};


#endif //CUSTOMVIDEOPLAYER_IDECODE_H
