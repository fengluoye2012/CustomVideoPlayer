//
// Created by wjw on 2019-10-31.
//

#include "FFDecode.h"
#include "LogUtils.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

bool FFDecode::open(XParameter para) {

    if (!para.para) {
        return false;
    }

    AVCodecParameters *p = para.para;

    //1 查找解码器
    AVCodec *cd = avcodec_find_decoder(p->codec_id);
    if (!cd) {
        LOGI(TAG, "avcodec_find_decoder failed");
        return false;
    }
    LOGI(TAG, "avcodec_find_decoder success");

    //2 创建解码上下文 并复制参数
    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec, p);

    //3 打开解码器
    int ret = avcodec_open2(codec, 0, nullptr);
    if (ret != 0) {
        char buf[1024] = {0};
        av_strerror(ret, buf, sizeof(buf) - 1);
        LOGI(TAG, "%s", buf);
        return false;
    }

    LOGI(TAG, "avcodec_open2 success");

    return true;
}
