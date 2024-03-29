//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_XSHADER_H
#define CUSTOMVIDEOPLAYER_XSHADER_H

#include <mutex>

enum XShaderType {
    XSHADER_YUV420P = 0, //软解码和虚拟机
    XSHADER_NV12 = 25,   //手机
    XSHADER_NV21 = 26
};

class XShader {
public:

    virtual bool init(XShaderType type = XSHADER_YUV420P);

    virtual void close();

    //获取材质并映射到内存中
    virtual void getTexture(unsigned int index, int width, int height, unsigned char *buf, bool isa= false);

    virtual void draw();

protected:

    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0};
    std::mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_XSHADER_H
