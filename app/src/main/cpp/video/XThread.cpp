//
// Created by wjw on 2019-10-30.
//

#include "XThread.h"
#include "thread"
#include "LogUtils.h"
#include "native-lib.h"

using namespace std;

void XSleep(int mis) {
    chrono::microseconds du(mis);
    this_thread::sleep_for(du);
}

bool XThread::start() {
    isExit = false;

    //成员函数作为指针函数传参；
    thread th(&XThread::threadMain, this);
    th.detach();
    return true;
}

void XThread::threadMain() {
    isRunning = true;
    LOGI(TAG, "线程函数进入");
    main();
    LOGI(TAG, "线程函数退出");
    isRunning = false;
}


void XThread::stop() {
    LOGI(TAG, "Stop 停止线程begin");
    isExit = true;
    for (int i = 0; i < 200; ++i) {
        if (!isRunning) {
            LOGI(TAG, "Stop 停止线程成功");
            return;
        }
        XSleep(1);
    }
    LOGI(TAG, "Stop 停止线程超时");
}