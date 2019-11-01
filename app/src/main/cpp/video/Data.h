//
// Created by wjw on 2019-10-31.
//

#ifndef CUSTOMVIDEOPLAYER_DATA_H
#define CUSTOMVIDEOPLAYER_DATA_H


struct Data {
    unsigned char *data = 0;
    int size = 0;
    bool isAudio = false;

    void Drop();
};


#endif //CUSTOMVIDEOPLAYER_DATA_H
