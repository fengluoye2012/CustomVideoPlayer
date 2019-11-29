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
   string str =  string("IDemux");
    while (!isExit) {
        XData data = read();
        if (data.size > 0) {
            data.tag = str.data();
            notify(data);
        }
    }
}
