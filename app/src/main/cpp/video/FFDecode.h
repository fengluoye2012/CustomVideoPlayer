//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_FFDECODE_H
#define CUSTOMVIDEOPLAYER_FFDECODE_H

#include "IDecode.h"
#define TAG "FFDecode"

struct AVCodecContext;

class FFDecode : public IDecode {
public:
    virtual bool open(XParameter para);

protected:

    AVCodecContext *codec = nullptr;

};


#endif //CUSTOMVIDEOPLAYER_FFDECODE_H
