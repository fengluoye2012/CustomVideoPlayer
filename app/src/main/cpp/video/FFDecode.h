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

    virtual bool open(XParameter para, bool isHard = false) override;

    virtual void close() override;

    virtual bool sendPacket(Data pkt) override;

    virtual Data recvFrame() override;

protected:

    AVCodecContext *codec = nullptr;
    AVFrame *frame = nullptr;
    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_FFDECODE_H
