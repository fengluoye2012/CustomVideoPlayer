//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_XPARAMETER_H
#define CUSTOMVIDEOPLAYER_XPARAMETER_H

struct AVCodecParameters;

class XParameter {

public:
    AVCodecParameters *para = nullptr;
    int channels = 2;
    int sample_rate = 44100;
};


#endif //CUSTOMVIDEOPLAYER_XPARAMETER_H
