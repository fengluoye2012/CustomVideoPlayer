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

void FFResample::close() {
    mux.lock();
    if (actx) {
        swr_free(&actx);
    }
    mux.unlock();
}

bool FFResample::open(XParameter in, XParameter out) {
    close();

    mux.lock();

    //音频重采样上下文初始化
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx, av_get_default_channel_layout(out.channels), AV_SAMPLE_FMT_S16,
                              out.sample_rate, av_get_default_channel_layout(in.para->channels),
                              (AVSampleFormat) in.para->format, in.para->sample_rate, 0, 0);

    int re = swr_init(actx);

    if (re != 0) {
        mux.unlock();
        LOGE(TAG, "swr_init failed");
        return false;
    }
    LOGE(TAG, "swr_init success");

    outChannels = in.para->channels;
    outFormat = AV_SAMPLE_FMT_S16;
    mux.unlock();
    return true;
}

XData FFResample::resample(XData inData) {

    if (inData.size <= 0 || !inData.data) {
        return XData();
    }

    mux.lock();
    if (!actx) {
        mux.unlock();
        return XData();
    }

    AVFrame *frame = (AVFrame *) inData.data;

    //输出空间的分配
    XData out;
    int outSize =
            outChannels * frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat) outFormat);

    if (outSize <= 0) {
        return XData();
    }

    out.Alloc(outSize);
    uint8_t *outArr[2] = {0};
    outArr[0] = out.data;
    int len = swr_convert(actx, outArr, frame->nb_samples, (const uint8_t **) frame->data,
                          frame->nb_samples);
    if (len <= 0) {
        mux.unlock();
        out.Drop();
        return XData();
    }

    out.pts = inData.pts;
    mux.unlock();
    LOGE(TAG, "swr_convert success");
    return out;
}


