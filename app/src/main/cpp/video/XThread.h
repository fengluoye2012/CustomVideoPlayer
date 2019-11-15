//
// Created by wjw on 2019-10-30.
//

#ifndef CUSTOMVIDEOPLAYER_XTHREAD_H
#define CUSTOMVIDEOPLAYER_XTHREAD_H


//单位是毫秒
void XSleep(int mis);

class XThread {

public:

    //启动线程
    virtual bool start();

    //通过控制isExit安全停止线程（不一定成功）
    virtual void stop();

    //入口主函数
    virtual void main() {};

protected:
    bool isExit = false;
    bool isRunning = false;

private:
    void threadMain();
};


#endif //CUSTOMVIDEOPLAYER_XTHREAD_H
