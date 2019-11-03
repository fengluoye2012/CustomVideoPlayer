//
// Created by wjw on 2019-10-31.
//

#include "IDecode.h"
#include "LogUtils.h"
#include "native-lib.h"

void IDecode::update(Data pkt) {

    if (pkt.isAudio != isAudio) {
        return;
    }

    while (!isExit) {
        packMutex.lock();

        //阻塞
        if (packs.size() < maxList) {
            //生产者
            packs.push_back(pkt);
            packMutex.unlock();
            break;
        }
        packMutex.unlock();
        XSleep(1);
    }
}


void IDecode::main() {
    while (!isExit) {
        packMutex.lock();
        if (packs.empty()) {
            packMutex.unlock();
            XSleep(1);
            continue;
        }

        //取出packet 消费
        Data pack = packs.front();
        packs.pop_front();

        //发送数据到解码线程，
        while (this->sendPacket(pack)) {
            while (!isExit) {
                //获取解码数据
                Data frame = recvFrame();
                if (!frame.data) {
                    break;
                }

                LOGI(TAG, "RecvFrame %d", frame.size);

                //发送数据给观察者
                this->notify(frame);
            }
        }

        pack.Drop();
        packMutex.unlock();
    }
}
