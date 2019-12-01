//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_IVIDEOVIEW_H
#define CUSTOMVIDEOPLAYER_IVIDEOVIEW_H

#include "XData.h"
#include "IObserver.h"
#include "LogUtils.h"
#include "native-lib.h"

class IVideoView : public IObserver {

public:
    virtual void setRender(void *win) = 0;
    virtual void render(XData data) = 0;
    virtual void update(XData data);
    virtual void close() = 0;
};

#endif //CUSTOMVIDEOPLAYER_IVIDEOVIEW_H
