//
// Created by wjw on 2019-11-03.
//

#include <mutex>
#include "XTexture.h"
#include "XShader.h"
#include "LogUtils.h"
#include "native-lib.h"
#include "XEGL.h"


class CXTexture : public XTexture {
public:
    XShader sh;
    XTextureType type;
    std::mutex mux;

    virtual void drop() override {
        mux.lock();
        XEGL::get()->close();
        sh.close();
        mux.unlock();
        delete this;
    }

    virtual bool init(void *win, XTextureType type) override {
        mux.lock();
        XEGL::get()->close();
        sh.close();
        this->type = type;

        if (!win) {
            mux.unlock();
            LOGE(TAG, "XTexture init failed win is NULL");
            return false;
        }

        if (!XEGL::get()->init(win)) {
            mux.unlock();
            return false;
        }

        sh.init();
        mux.unlock();
        return true;
    }

    virtual void draw(unsigned char *data[], int width, int height) override {
        mux.lock();

        sh.getTexture(0, width, height, data[0]); //Y
        if (type == XTEXTURE_YUV420P) {
            sh.getTexture(1, width / 2, height / 2, data[1]); // U
            sh.getTexture(2, width / 2, height / 2, data[2]); //V
        } else {
            sh.getTexture(1, width / 2, height / 2, data[1], true); //UV
        }

        sh.draw();
        XEGL::get()->draw();
        mux.unlock();
    }


};


XTexture *XTexture::create() {
    return new CXTexture();
}
