//
// Created by wjw on 2019-11-13.
//

#include "FFPlayerBuilder.h"
#include "FFDecode.h"
#include "FFDemux.h"
#include "FFResample.h"
#include "GLVideoView.h"
#include "SLAudioPlay.h"

void FFPlayerBuilder::initHard(void *vm) {
    FFDecode::initHard(vm);
}

IDemux *FFPlayerBuilder::createDemux() {
    IDemux *ff = new FFDemux();
    return ff;
}

IDecode *FFPlayerBuilder::createDecode() {
    IDecode *decode = new FFDecode();
    return decode;
}

IResample *FFPlayerBuilder::createResample() {
    IResample *resample = new FFResample();
    return resample;
}

IVideoView *FFPlayerBuilder::createVideoView() {
    IVideoView *videoView = new GLVideoView();
    return videoView;
}

IAudioPlay *FFPlayerBuilder::createAudioPlay() {
    IAudioPlay *audioPlay = new SLAudioPlay();
    return audioPlay;
}

IPlayer *FFPlayerBuilder::createPlayer(unsigned char index) {
    return IPlayer::get(index);
}
