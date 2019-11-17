//
// Created by wjw on 2019-11-03.
//

#include "IAudioPlay.h"
#include "LogUtils.h"

XData IAudioPlay::getData() {
    XData d;
    while (!isExit) {
        framesMutex.lock();
        if (!frames.empty()) {
            //有数据返回
            d = frames.front();
            frames.pop_front();
            framesMutex.unlock();
            pts = d.pts;
            return d;
        }

        framesMutex.unlock();
        XSleep(1);
    }

    //未获取数据
    return d;
}


void IAudioPlay::update(XData data) {
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