//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_XTEXTURE_H
#define CUSTOMVIDEOPLAYER_XTEXTURE_H


class XTexture {

public:

    static XTexture *create();

    virtual bool init(void *win) = 0;

    virtual void draw(unsigned char *data[], int width, int height) = 0;


};


#endif //CUSTOMVIDEOPLAYER_XTEXTURE_H
