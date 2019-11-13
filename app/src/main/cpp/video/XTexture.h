//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_XTEXTURE_H
#define CUSTOMVIDEOPLAYER_XTEXTURE_H

enum XTextureType {
    XTEXTURE_YUV420P = 0,  //Y 4  U 1 V 1
    XTEXTURE_NV12 = 25, //Y 4 UV 1
    XTEXTURE_NV21 = 26 //Y 4 VU 1
};


class XTexture {

public:

    static XTexture *create();

    virtual bool init(void *win, XTextureType type = XTEXTURE_YUV420P) = 0;

    virtual void draw(unsigned char *data[], int width, int height) = 0;

    virtual void drop() = 0;

    virtual ~XTexture() {};

protected:
    XTexture() {}
};


#endif //CUSTOMVIDEOPLAYER_XTEXTURE_H
