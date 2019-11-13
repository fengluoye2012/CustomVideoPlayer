//
// Created by wjw on 2019-11-12.
//

#include "FFResample.h"

extern "C" {
#include <libswresample/swresample.h>
#include <libavcodec/avcodec.h>
}

#include "LogUtils.h"
#include "native-lib.h"

bool FFResample::open(XParameter in, XParameter out) {

    //音频重采样上下文初始化
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx, av_get_default_channel_layout(out.channels), AV_SAMPLE_FMT_S16,
                              out.sample_rate, av_get_default_channel_layout(in.para->channels),
                              (AVSampleFormat) in.para->format, in.para->sample_rate, 0, nullptr);

    int re = swr_init(actx);

    if (re != 0) {
        LOGE(TAG, "swr_init failed");
        return false;
    }
    LOGE(TAG, "swr_init success");

    outChannels = in.para->channels;
    outFormat = AV_SAMPLE_FMT_S16;
    return true;
}

Data FFResample::resample(Data inData) {

    if (inData.size <= 0 || inData.data) {
        return Data();
    }

    if (!actx) {
        return Data();
    }

    AVFrame *frame = (AVFrame *) inData.data;

    //输出空间的分配
    Data out;
    int outSize =
            outChannels * frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat) outFormat);

    if (outSize <= 0) {
        return Data();
    }

    out.Alloc(outSize);
    uint8_t *outArr[2] = {nullptr};
    outArr[0] = out.data;
    int len = swr_convert(actx, outArr, frame->nb_samples, (const uint8_t **) frame->data,
                          frame->nb_samples);
    if (len <= 0) {
        out.Drop();
        return Data();
    }
    LOGE(TAG, "swr_convert success");
    return out;
}
