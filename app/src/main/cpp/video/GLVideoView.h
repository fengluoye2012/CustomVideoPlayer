//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_GLVIDEO_H
#define CUSTOMVIDEOPLAYER_GLVIDEO_H

#include "IVideoView.h"

class XTexture;

class GLVideoView : public IVideoView {

public:

    virtual void setRender(void *win);

    virtual void render(Data data);


protected:
    void *view = nullptr;
    XTexture *txt = nullptr;

};


#endif //CUSTOMVIDEOPLAYER_GLVIDEO_H
