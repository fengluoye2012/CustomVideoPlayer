//
// Created by wjw on 2019-11-03.
//

#include "IVideoView.h"
#include "LogUtils.h"
#include "native-lib.h"

void IVideoView::update(XData data) {
    LOGI(TAG, "IVideoView::update == %s", data.tag);
    this->render(data);
}
