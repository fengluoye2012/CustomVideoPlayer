//
// Created by wjw on 2019-11-03.
//

#ifndef CUSTOMVIDEOPLAYER_XEGL_H
#define CUSTOMVIDEOPLAYER_XEGL_H


class XEGL {

public:

    virtual bool init(void *win) = 0;

    virtual void close() = 0;

    virtual void draw() = 0;

    static XEGL *get();

protected:
    XEGL() {}
};


#endif //CUSTOMVIDEOPLAYER_XEGL_H
