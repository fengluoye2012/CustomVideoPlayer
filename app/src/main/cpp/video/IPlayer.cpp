//
// Created by wjw on 2019-11-12.
//

#include "IPlayer.h"
#include "LogUtils.h"
#include "IDemux.h"
#include "native-lib.h"
#include "IDecode.h"
#include "LogUtils.h"
#include "IResample.h"
#include "IAudioPlay.h"
#include "IVideoView.h"

bool IPlayer::start() {
    if (!demux || !demux->start()) {
        return false;
    }

    if (aDecode) {
        aDecode->start();
    }

    if (audioPlay) {
        audioPlay->startPlay(outPara);
    }

    if (vDecode) {
        vDecode->start();
    }
    return true;
}

IPlayer *IPlayer::get(unsigned char index) {
    static IPlayer p[256];
    return &p[index];
}

bool IPlayer::open(const char *path) {

    //解封装
    if (!demux || !demux->open(path)) {
        LOGE(TAG, "demux open %s failed ", path);
        return false;
    }

    //解码 解码可能不需要，如果是解封之后就是原始数据
    if (!vDecode || !vDecode->open(demux->getVPara(), isHardDecode)) {
        LOGE(TAG, "vDecode->open %s failed", path);
    }

    if (!aDecode || !aDecode->open(demux->getAPara())) {
        LOGE(TAG, "aDecode->open %s failed", path);
    }

    //重采样 有可能不需要要，解码后或者解封后可能是直接能播放的数据
    if (outPara.sample_rate <= 0) {
        outPara = demux->getAPara();
    }

    if (!resample || resample->open(demux->getAPara(), outPara)) {
        LOGE(TAG, "resample->open %s failed", path);
    }

    return true;
}

void IPlayer::initView(void *win) {
    if(videoView){
        videoView->setRender(win);
    }
}
