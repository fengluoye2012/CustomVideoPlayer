//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_GLVIDEO_H
#define CUSTOMVIDEOPLAYER_GLVIDEO_H

#include "IVideoView.h"
#include "XData.h"

class XTexture;

class GLVideoView: public IVideoView {
public:
    virtual void setRender(void *win);
    virtual void render(XData data);
    virtual void close();
protected:
    void *view = 0;
    XTexture *txt = 0;
    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_GLVIDEO_H
