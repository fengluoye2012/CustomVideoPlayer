//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_IAUDIOPLAY_H
#define CUSTOMVIDEOPLAYER_IAUDIOPLAY_H

#include "IObserver.h"
#include "XParameter.h"
#include <iostream>
#include <list>

class IAudioPlay : public IObserver {

public:

    //缓冲满后 阻塞
    virtual void update(Data data);

    //获取缓冲数据，如果没有 则阻塞
    virtual Data getData();


    virtual bool startPlay(XParameter out) = 0;

    //最大缓冲
    int maxFrame = 100;

protected:
    std::list<Data> frames;
    std::mutex framesMutex;
};


#endif //CUSTOMVIDEOPLAYER_IAUDIOPLAY_H
