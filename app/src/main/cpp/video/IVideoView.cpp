//
// Created by wjw on 2019-11-03.
//

#include "IVideoView.h"
#include "LogUtils.h"
#include "native-lib.h"

void IVideoView::update(XData data)
{
    LOGI(TAG,"IVideoView::update ");//无法调用
    this->render(data);
}
