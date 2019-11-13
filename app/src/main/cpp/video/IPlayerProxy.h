//
// Created by wjw on 2019-11-13.
//

#ifndef CUSTOMVIDEOPLAYER_IPLAYERPROXY_H
#define CUSTOMVIDEOPLAYER_IPLAYERPROXY_H

#include <mutex>
#include "IPlayer.h"

class IPlayerProxy : public IPlayer {

public:

    static IPlayerProxy *get() {
        static IPlayerProxy px;
        return &px;
    }

    void init(void *vm = nullptr);

    virtual bool open(const char *path) override;

    virtual bool start() override;

    virtual void initView(void *win) override;

protected:
    IPlayerProxy() {}

    IPlayer *player = nullptr;
    std::mutex mux;

};


#endif //CUSTOMVIDEOPLAYER_IPLAYERPROXY_H
