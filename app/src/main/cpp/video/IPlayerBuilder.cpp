//
// Created by wjw on 2019-11-13.
//

#include "IPlayerBuilder.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IVideoView.h"
#include "IResample.h"
#include "IAudioPlay.h"

IPlayer *IPlayerBuilder::builderPlayer(unsigned char index) {

    IPlayer *play = createPlayer(index);

    //解封转
    IDemux *de = createDemux();

    //视频解封装
    IDecode *vDecode = createDecode();

    //音频解封装
    IDecode *aDecode = createDecode();


    //解码器观察解封装
    de->addObs(vDecode);
    de->addObs(aDecode);

    //显示观察视频解码器
    IVideoView *view = createVideoView();
    vDecode->addObs(view);

    //重采样观察音频解码器
    IResample *resample = createResample();
    aDecode->addObs(resample);

    //音频播放观察重采样
    IAudioPlay *audioPlay = createAudioPlay();
    resample->addObs(audioPlay);


    play->demux = de;
    play->aDecode = aDecode;
    play->vDecode = vDecode;
    play->videoView = view;
    play->resample = resample;
    play->audioPlay = audioPlay;

    return play;
}
