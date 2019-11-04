//
// Created by wjw on 2019-11-03.
//

#include "IAudioPlay.h"

void IAudioPlay::update(Data data) {

    //压入缓冲队列
    if (data.size <= 0 || !data.data) {
        return;
    }

    while (!isExit) {
        framesMutex.lock();
        if (frames.size() > maxFrame) {
            framesMutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        framesMutex.unlock();
        break;
    }
}

Data IAudioPlay::getData() {
    Data d;
    while (!isExit) {
        framesMutex.lock();
        if (!frames.empty()) {
            d = frames.front();
            frames.pop_front();
            framesMutex.unlock();
            return d;
        }

        framesMutex.unlock();
        XSleep(1);
    }
    return d;
}
