//
// Created by wjw on 2019-10-30.
//

#include "IObserver.h"
#include "LogUtils.h"
#include "native-lib.h"
#include "string.h"
#include "iostream"
#include "cstring"
#include "iostream"

using namespace std;
using std::string;


void IObserver::addObs(IObserver *obs) {
    LOGI(TAG, "IObserver::addObs obs");
    if (!obs) {
        LOGI(TAG, "IObserver::addObs obs = null");
        return;
    }

    LOGI(TAG, "IObserver::addObs==  %s", typeid(obs).name());
    mux.lock();
    //向尾部添加一个元素
    obss.push_back(obs);
    mux.unlock();

}


void IObserver::notify(XData data) {
    mux.lock();
    for (int i = 0; i < obss.size(); i++) {
        LOGI(TAG, "notify ：：%s,,,i== %d", data.tag, i);
        //调用update();
        obss[i]->update(data);
    }
    mux.unlock();
}
