//
// Created by wjw on 2019-11-13.
//

#include "IPlayerProxy.h"
#include "FFPlayerBuilder.h"

void IPlayerProxy::init() {
    mux.lock();
//    if (vm) {
//        FFPlayerBuilder::initHard(vm);
//    }

    if (!player) {
        player = FFPlayerBuilder::get()->builderPlayer();
    }
    mux.unlock();
}


bool IPlayerProxy::open(const char *path) {
    bool re = false;
    mux.lock();
    if (player) {
        re = player->open(path);
    }
    mux.unlock();
    return re;
}

bool IPlayerProxy::start() {
    bool re = false;
    mux.lock();
    if (player) {
        re = player->start();
    }
    mux.unlock();
    return re;
}

void IPlayerProxy::initView(void *win) {
    mux.lock();
    if (player) {
        player->initView(win);
    }
    mux.unlock();
}

