//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_XSHADER_H
#define CUSTOMVIDEOPLAYER_XSHADER_H

enum XShaderType {
    XSHADER_YUV420P = 0, //软解码和虚拟机
    XSHADER_NV12 = 25,   //手机
    XSHADER_NV21 = 26
};

class XShader {
public:

    virtual bool init(XShaderType type = XSHADER_YUV420P);

    virtual void getTexture(unsigned int index, int width, int height, unsigned char *buf);

    virtual void draw();

protected:

    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};

};


#endif //CUSTOMVIDEOPLAYER_XSHADER_H
