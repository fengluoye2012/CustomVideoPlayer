//
// Created by wjw on 2019-10-30.
//

#ifndef CUSTOMVIDEOPLAYER_XTHREAD_H
#define CUSTOMVIDEOPLAYER_XTHREAD_H


//sleep 毫秒
void XSleep(int mis);

//c++ 11 线程库
class XThread {
public:
    //启动线程
    virtual bool start();

    //通过控制isExit安全停止线程（不一定成功）
    virtual void stop();

    //入口主函数
    virtual void main() {}

protected:
    bool isExit = false;
    bool isRuning = false;
private:
    void ThreadMain();

};


#endif //CUSTOMVIDEOPLAYER_XTHREAD_H
