//
// Created by wjw on 2019-10-31.
//

#include "IDemux.h"
#include "XData.h"
#include "LogUtils.h"
#include "native-lib.h"
#include "cstring"
#include "iostream"

using namespace std;
using std::string;

void IDemux::main() {
    while (!isExit) {

        XData d = read();
        if (d.size > 0)
            notify(d);
        //XLOGI("IDemux Read %d",d.size);
        //if(d.size<=0)break;
    }
}
