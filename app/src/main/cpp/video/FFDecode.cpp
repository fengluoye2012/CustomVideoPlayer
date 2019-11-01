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

    if (codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        this->isAudio = false;
    } else if (codec->codec_type == AVMEDIA_TYPE_AUDIO) {
        this->isAudio = true;
    }

    return true;
}

bool FFDecode::sendPacket(Data pkt) {
    if (pkt.size <= 0 || !pkt.data) {
        return false;
    }

    if (!codec) {
        return false;
    }

    int ret = avcodec_send_packet(codec, (AVPacket *) pkt.data);

    return ret == 0;
}

//从线程中获取解码结果
Data FFDecode::recvFrame() {

    if (!codec) {
        return Data();
    }

    if (!frame) {
        frame = av_frame_alloc();
    }

    int ret = avcodec_receive_frame(codec, frame);

    if (ret != 0) {
        return Data();
    }

    Data data;
    data.data = (unsigned char *) frame;

    if (codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        data.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
    } else if (codec->codec_type == AVMEDIA_TYPE_AUDIO) {
        //样本字节数 * 单通道样本数*通道数
        data.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * 2;
    } else {
        return Data();
    }

    return data;
}
