//
// Created by wjw on 2019-11-12.
//

#include "IResample.h"

void IResample::update(XData data) {
    XData d = this->resample(data);
    if (d.size > 0) {
        this->notify(d);
    }
}
