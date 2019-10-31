//
// Created by wjw on 2019-10-31.
//

#include "IDemux.h"
#include "Data.h"

void IDemux::main() {
    while (!isExit) {
        Data data = read();

        if (data.size > 0) {
            notify(data);
        }
    }
}
