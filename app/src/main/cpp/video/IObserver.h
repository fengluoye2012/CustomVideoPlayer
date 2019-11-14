//
// Created by wjw on 2019-10-30.
//

#ifndef CUSTOMVIDEOPLAYER_IOBSERVER_H
#define CUSTOMVIDEOPLAYER_IOBSERVER_H

#include <iostream>
#include "Data.h"
#include <vector>
#include "XThread.h"

using namespace std;
using std::vector;


//观察者和主体  继承线程
class IObserver : public XThread {

public:

    //主体函数 添加观察者（线程安全）
    void addObs(IObserver *obs);

    //观察者接受数据函数
    virtual void update(Data data) {};

    //通知所有观察者（线程安全）
    void notify(Data data);

protected:
    //vector 数据结构
    vector<IObserver *> obss;
    //互斥锁
    mutex mux;
};


#endif //CUSTOMVIDEOPLAYER_IOBSERVER_H
