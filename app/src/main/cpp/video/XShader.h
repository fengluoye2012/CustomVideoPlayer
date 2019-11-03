//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_XSHADER_H
#define CUSTOMVIDEOPLAYER_XSHADER_H


class XShader {
public:

    virtual bool init();

    virtual void getTexture(unsigned int index, int width, int height, unsigned char *buf);

    virtual void draw();

protected:

    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};

};


#endif //CUSTOMVIDEOPLAYER_XSHADER_H
