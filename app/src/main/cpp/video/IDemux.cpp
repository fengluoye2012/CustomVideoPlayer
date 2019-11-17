//
// Created by wjw on 2019-10-31.
//

#include "IDemux.h"
#include "XData.h"
#include "LogUtils.h"
#include "native-lib.h"

void IDemux::main() {
    while (!isExit) {
        XData data = read();

        if (data.size > 0) {
            //LOGI(TAG,"IDemux::main");
            notify(data);
        }
    }
}
