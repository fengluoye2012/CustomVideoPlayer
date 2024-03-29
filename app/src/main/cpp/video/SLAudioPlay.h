//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_SLAUDIOPLAY_H
#define CUSTOMVIDEOPLAYER_SLAUDIOPLAY_H


#include "IAudioPlay.h"

class SLAudioPlay : public IAudioPlay {

public:

    virtual bool startPlay(XParameter out);

    void close();

    void playCall(void *bufq);

    SLAudioPlay();

    virtual ~SLAudioPlay();

protected:
    unsigned char *buf = 0;
    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_SLAUDIOPLAY_H
