//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_IVIDEOVIEW_H
#define CUSTOMVIDEOPLAYER_IVIDEOVIEW_H

#include "Data.h"
#include "IObserver.h"

class IVideoView : public IObserver {

public:

    virtual void setRender(void *win) = 0;

    virtual void render(Data data) = 0;

    virtual void update(Data data);

    virtual void close() = 0;
};


#endif //CUSTOMVIDEOPLAYER_IVIDEOVIEW_H
