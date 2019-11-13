//
// Created by wjw on 2019-10-31.
//

#include "IDecode.h"
#include "LogUtils.h"
#include "native-lib.h"

//由主体notify 的数据
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

        //判断音视频同步
        if (!isAudio && synPts > 0) {
            if (synPts < pts) {
                packMutex.unlock();
                XSleep(1);
                continue;
            }
        }

        if (packs.empty()) {
            packMutex.unlock();
            XSleep(1);
            continue;
        }

        //取出packet 消费者
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

                //LOGI(TAG, "RecvFrame %d", frame.size);
                pts = frame.pts;

                //发送数据给观察者
                this->notify(frame);
            }
        }

        pack.Drop();
        packMutex.unlock();
    }
}
