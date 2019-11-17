//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_FFDECODE_H
#define CUSTOMVIDEOPLAYER_FFDECODE_H

#include "IDecode.h"
#include "XParameter.h"


struct AVCodecContext;
struct AVFrame;

class FFDecode : public IDecode {
public:

    static void initHard(void *vm);

    virtual bool open(XParameter para, bool isHard = false);

    virtual void close();

    virtual bool sendPacket(XData pkt);

    virtual XData recvFrame();

protected:

    AVCodecContext *codec = nullptr;
    AVFrame *frame = 0;
    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_FFDECODE_H
