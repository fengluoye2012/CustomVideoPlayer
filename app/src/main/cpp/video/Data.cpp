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

bool Data::Alloc(int size, const char *data) {

    Drop();
    type = UCHAR_TYPE;

    if (size <= 0) {
        return false;
    }

    this->data = new unsigned char[size];
    if (!this->data) {
        return false;
    }

    if (data) {
        memcpy(this->data, data, size);
    }

    this->size = size;

    return true;
}
