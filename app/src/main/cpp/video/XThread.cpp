//
// Created by wjw on 2019-10-30.
//

#include "XThread.h"
#include "thread"
#include "LogUtils.h"
#include "native-lib.h"

using namespace std;

void XSleep(int mis) {
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

//启动线程
bool XThread::start() {
    isExit = false;
    thread th(&XThread::ThreadMain, this);
    th.detach();
    return true;
}

void XThread::ThreadMain() {
    isRuning = true;
    LOGI(TAG, "线程函数进入");
    main();
    LOGI(TAG, "线程函数退出");
    isRuning = false;
}


//通过控制isExit安全停止线程（不一定成功）
void XThread::stop() {
    LOGI(TAG, "Stop 停止线程begin!");
    isExit = true;
    for (int i = 0; i < 200; i++) {
        if (!isRuning) {
            LOGI(TAG, "Stop 停止线程成功!");
            return;
        }
        XSleep(1);
    }
    LOGI(TAG, "Stop 停止线程超时!");

}