//
// Created by wjw on 2019-10-31.
//

#include "Data.h"

extern "C" {
#include <libavformat/avformat.h>
}

void Data::Drop() {
    if (!data) {
        return;
    }
    av_packet_free((AVPacket **) &data);

    data = nullptr;
    size = 0;
}
