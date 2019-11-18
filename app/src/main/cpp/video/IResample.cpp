//
// Created by wjw on 2019-11-12.
//

#include "IResample.h"

#include "LogUtils.h"
#include "native-lib.h"

void IResample::update(XData data) {
    //LOGI(TAG,"IResample::update"); //可以调用
    XData d = this->resample(data);
    if (d.size > 0) {
        //LOGI(TAG,"%s  ==调用notity", typeid(this).name());
        this->notify(d);
    }
}
