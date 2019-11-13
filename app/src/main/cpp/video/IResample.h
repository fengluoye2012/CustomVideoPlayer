//
// Created by wjw on 2019-11-12.
//

#ifndef CUSTOMVIDEOPLAYER_IRESAMPLE_H
#define CUSTOMVIDEOPLAYER_IRESAMPLE_H


#include "IObserver.h"
#include "XParameter.h"

class IResample : public IObserver {
public:

    //纯虚函数，设置默认值
    virtual bool open(XParameter in, XParameter out = XParameter()) = 0;

    virtual void close() = 0;

    virtual Data resample(Data inData) = 0;

    virtual void update(Data data);

    int outChannels = 2;
    int outFormat = 1;
};


#endif //CUSTOMVIDEOPLAYER_IRESAMPLE_H
