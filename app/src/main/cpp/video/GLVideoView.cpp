//
// Created by wjw on 2019-11-03.
//

#include "GLVideoView.h"
#include "XTexture.h"
#include "LogUtils.h"
#include "native-lib.h"

void GLVideoView::setRender(void *win)
{
    view = win;
}
void GLVideoView::close()
{
    mux.lock();
    if(txt)
    {
        txt->drop();
        txt = 0;
    }

    mux.unlock();
}
void GLVideoView::render(XData data)
{

    LOGI(TAG,"GLVideoView::render");
    if(!view) return;
    if(!txt)
    {
        txt = XTexture::create();

        txt->init(view,(XTextureType)data.format);
    }
    txt->draw(data.datas,data.width,data.height);
}


