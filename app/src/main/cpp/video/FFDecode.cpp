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
    av_jni_set_java_vm(vm, 0);
}

void FFDecode::close() {
    mux.lock();
    pts = 0;
    if (frame)
        av_frame_free(&frame);
    if (codec) {
        avcodec_close(codec);
        avcodec_free_context(&codec);
    }
    mux.unlock();
}

bool FFDecode::open(XParameter para, bool isHard) {
    close();
    if (!para.para) return false;
    AVCodecParameters *p = para.para;

    //1 查找解码器
    AVCodec *cd = avcodec_find_decoder(p->codec_id);
//    if(isHard)
//    {
//        cd = avcodec_find_decoder_by_name("h264_mediacodec");
//    }

    if (!cd) {
        return false;
    }

    mux.lock();
    //2 创建解码上下文，并复制参数
    codec = avcodec_alloc_context3(cd);
    avcodec_parameters_to_context(codec, p);

    codec->thread_count = 8;
    //3 打开解码器
    int re = avcodec_open2(codec, 0, 0);
    if (re != 0) {
        mux.unlock();
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf) - 1);
        return false;
    }

    if (codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        this->isAudio = false;
    } else {
        this->isAudio = true;
    }
    mux.unlock();
    return true;
}

bool FFDecode::sendPacket(XData pkt) {
    if (pkt.size <= 0 || !pkt.data)return false;
    mux.lock();
    if (!codec) {
        mux.unlock();
        return false;
    }
    int re = avcodec_send_packet(codec, (AVPacket *) pkt.data);
    mux.unlock();
    if (re != 0) {
        return false;
    }
    return true;
}

//从线程中获取解码结果
XData FFDecode::recvFrame() {
    mux.lock();
    if (!codec) {
        mux.unlock();
        return XData();
    }
    if (!frame) {
        frame = av_frame_alloc();
    }
    int re = avcodec_receive_frame(codec, frame);
    if (re != 0) {
        mux.unlock();
        return XData();
    }
    XData d;
    d.data = (unsigned char *) frame;
    if (codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
        d.width = frame->width;
        d.height = frame->height;
    } else {
        //样本字节数 * 单通道样本数 * 通道数
        d.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * 2;
    }
    d.format = frame->format;
    //if(!isAudio)
    //    XLOGE("data format is %d",frame->format);
    memcpy(d.datas, frame->data, sizeof(d.datas));
    d.pts = frame->pts;
    pts = d.pts;
    mux.unlock();
    return d;
}


