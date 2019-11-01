//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_FFDECODE_H
#define CUSTOMVIDEOPLAYER_FFDECODE_H

#include "IDecode.h"

#define TAG "FFDecode"

struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode {
public:

    virtual bool open(XParameter para);

    bool sendPacket(Data pkt) override;

    Data recvFrame() override;

protected:

    AVCodecContext *codec = nullptr;

    AVFrame *frame = nullptr;
};


#endif //CUSTOMVIDEOPLAYER_FFDECODE_H
