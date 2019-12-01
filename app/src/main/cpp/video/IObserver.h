//
// Created by wjw on 2019-10-30.
//

#ifndef CUSTOMVIDEOPLAYER_IOBSERVER_H
#define CUSTOMVIDEOPLAYER_IOBSERVER_H

#include <iostream>
#include "XData.h"
#include <vector>
#include "XThread.h"


//观察者 和 主体
class IObserver : public XThread {
public:
    //观察者接收数据函数
    virtual void update(XData data) {}

    //主体函数 添加观察者(线程安全)
    void addObs(IObserver *obs);

    //通知所有观察者(线程安全)
    void notify(XData data);

protected:
    std::vector<IObserver *> obss;
    std::mutex mux;
};

#endif //CUSTOMVIDEOPLAYER_IOBSERVER_H
