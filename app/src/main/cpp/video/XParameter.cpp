//
// Created by wjw on 2019-10-31.
//

#include "XParameter.h"

AVCodecParameters *XParameter::getPara() const {
    return para;
}

void XParameter::setPara(AVCodecParameters *para) {
    XParameter::para = para;
}
