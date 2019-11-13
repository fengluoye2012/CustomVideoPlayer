//
// Created by wjw on 2019-11-12.
//

#include "IResample.h"

void IResample::update(Data data) {
    Data d = this->resample(data);
    if (d.size > 0) {
        this->notify(d);
    }
}
