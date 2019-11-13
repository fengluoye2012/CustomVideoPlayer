//
// Created by wjw on 2019-10-31.
//

#include "FFDecode.h"
#include "LogUtils.h"
#include "native-lib.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/jni.h>
}


void FFDecode::initHard(void *vm) {
    av_jni_set_java_vm(vm, nullptr);
}

bool FFDecode::open(XParameter para, bool isHard) {

    close();

    if (!para.para) {
        return false;
    }

    AVCodecParameters *p = para.para;

    //1 查找解码器
    AVCodec *cd = avcodec_find_decoder(p->codec_id);

    //硬解码
    if (isHard) {
        cd = avcodec_find_decoder_by_name("h264_mediacodec");
    }

    if (!cd) {
        LOGI(TAG, "avcodec_find_decoder failed");
        return false;
    }
    LOGI(TAG, "avcodec_find_decoder success");

    mux.lock();

    //2 创建解码上下文 并复制参数
    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec, p);
    //多线程解码
    codec->thread_count = 8;

    //3 打开解码器
    int ret = avcodec_open2(codec, nullptr, nullptr);
    if (ret != 0) {
        char buf[1024] = {0};
        av_strerror(ret, buf, sizeof(buf) - 1);
        LOGI(TAG, "%s", buf);
        return false;
    }

    this->isAudio = !(codec->codec_type == AVMEDIA_TYPE_VIDEO);
    mux.unlock();

    LOGI(TAG, "avcodec_open2 success");
    return true;
}

bool FFDecode::sendPacket(Data pkt) {
    if (pkt.size <= 0 || !pkt.data) {
        return false;
    }

    mux.lock();

    if (!codec) {
        mux.unlock();
        return false;
    }

    int ret = avcodec_send_packet(codec, (AVPacket *) pkt.data);

    mux.unlock();
    return ret == 0;
}

//从线程中获取解码结果
Data FFDecode::recvFrame() {

    mux.lock();
    if (!codec) {
        mux.unlock();
        return Data();
    }

    if (!frame) {
        frame = av_frame_alloc();
    }

    int ret = avcodec_receive_frame(codec, frame);

    if (ret != 0) {
        mux.unlock();
        return Data();
    }

    Data data;
    data.data = (unsigned char *) frame;

    if (codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        data.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
        data.width = frame->width;
        data.height = frame->height;
    } else {
        //样本字节数 * 单通道样本数*通道数
        data.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * 2;
    }

    memcpy(data.datas, frame->data, sizeof(data.datas));
    data.pts = static_cast<int>(frame->pts);
    pts = data.pts;
    mux.unlock();

    return data;
}

void FFDecode::close() {
    mux.lock();
    pts = 0;
    if (frame) {
        av_frame_free(&frame);
    }

    if (codec) {
        avcodec_close(codec);
        avcodec_free_context(&codec);
    }
    mux.unlock();
}

