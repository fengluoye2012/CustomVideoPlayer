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

    virtual IDemux *createDemux() override;

    virtual IDecode *createDecode() override;

    virtual IResample *createResample() override;

    virtual IVideoView *createVideoView() override;

    virtual IAudioPlay *createAudioPlay() override;

    virtual IPlayer *createPlayer(unsigned char index) override;
};


#endif //CUSTOMVIDEOPLAYER_FFPLAYERBUILDER_H
