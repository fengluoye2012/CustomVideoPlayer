//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_XPARAMETER_H
#define CUSTOMVIDEOPLAYER_XPARAMETER_H

struct AVCodecParameters;

class XParameter {

public:
    AVCodecParameters *para = nullptr;

    AVCodecParameters *getPara() const;

    void setPara(AVCodecParameters *para);

};


#endif //CUSTOMVIDEOPLAYER_XPARAMETER_H
