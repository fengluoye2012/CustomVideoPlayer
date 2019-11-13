//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_DATA_H
#define CUSTOMVIDEOPLAYER_DATA_H

enum DataType {
    AVPACKET_TYPE = 0,
    UCHAR_TYPE = 1
};


struct Data {
    int type = 0;
    unsigned char *data = 0;

    unsigned char *datas[8] = {0};

    int size = 0;
    bool isAudio = false;

    int width = 0;
    int height = 0;
    int format = 0;

    bool Alloc(int size, const char *data = nullptr);

    void Drop();
};


#endif //CUSTOMVIDEOPLAYER_DATA_H
