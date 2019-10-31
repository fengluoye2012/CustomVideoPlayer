//
// Created by wjw on 2019-10-30.
//

#include "IObserver.h"


void IObserver::addObs(IObserver *obs) {
    if (!obs) {
        return;
    }

    mux.lock();
    //向尾部添加一个元素
    obsVec.push_back(obs);
    mux.unlock();

}


void IObserver::notify(Data data) {
    mux.lock();
    for (int i = 0; i < obsVec.size(); i++) {
        obsVec[i]->notify(data);
    }
    mux.unlock();
}
