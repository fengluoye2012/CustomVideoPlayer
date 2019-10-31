//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_IDECODE_H
#define CUSTOMVIDEOPLAYER_IDECODE_H


#include "IObserver.h"
#include "XParameter.h"

//解码接口 支持硬解码
class IDecode : public IObserver {

public:

    //打开解码器
    virtual bool open(XParameter para) = 0;

};


#endif //CUSTOMVIDEOPLAYER_IDECODE_H
