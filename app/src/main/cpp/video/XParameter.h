//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_XPARAMETER_H
#define CUSTOMVIDEOPLAYER_XPARAMETER_H

struct AVCodecParameters;

class XParameter {

public:
    AVCodecParameters *para = nullptr;
    //音频的参数
    int channels = 2;//通道数
    int sample_rate = 44100; // 采样率
};


#endif //CUSTOMVIDEOPLAYER_XPARAMETER_H
