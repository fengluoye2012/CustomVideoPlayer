//
// Created by wjw on 2019-11-13.
//

#ifndef CUSTOMVIDEOPLAYER_FFPLAYERBUILDER_H
#define CUSTOMVIDEOPLAYER_FFPLAYERBUILDER_H


#include "IPlayerBuilder.h"

class FFPlayerBuilder : public IPlayerBuilder {
public:
    static void initHard(void *vm);

    static FFPlayerBuilder *get() {
        static FFPlayerBuilder ff;
        return &ff;
    }

protected:

    FFPlayerBuilder() {}

    virtual IDemux *createDemux();

    virtual IDecode *createDecode();

    virtual IResample *createResample();

    virtual IVideoView *createVideoView();

    virtual IAudioPlay *createAudioPlay();

    virtual IPlayer *createPlayer(unsigned char index = 0);
};


#endif //CUSTOMVIDEOPLAYER_FFPLAYERBUILDER_H
