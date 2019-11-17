//
// Created by wjw on 2019-11-12.
//

#ifndef CUSTOMVIDEOPLAYER_FFRESAMPLE_H
#define CUSTOMVIDEOPLAYER_FFRESAMPLE_H

#include "IResample.h"

struct SwrContext;

class FFResample : public IResample {

public:
    virtual bool open(XParameter in, XParameter out = XParameter());

    virtual void close();

    virtual XData resample(XData inData);

protected:
    SwrContext *actx = nullptr;
    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_FFRESAMPLE_H
