//
// Created by wjw on 2019-10-31.
//

#include "FFDemux.h"
#include "LogUtils.h"
#include "native-lib.h"

extern "C" {
#include "libavformat/avformat.h"
}

//分数转为浮点数
static double r2q(AVRational r) {
    return r.num == 0 || r.den == 0 ? 0. : (double) r.num / (double) r.den;
}

void FFDemux::close() {
    mux.lock();
    if (ic) {
        avformat_close_input(&ic);
    }
    mux.unlock();
}

bool FFDemux::open(const char *url) {

    LOGI(TAG, "open file %s begin", url);
    close();

    mux.lock();
    int ret = avformat_open_input(&ic, url, 0, 0);

    if (ret != 0) {
        mux.unlock();
        char buf[1024] = {0};
        LOGE(TAG, "open file %s failed", url);
        av_strerror(ret, buf, sizeof(buf));
        return false;
    }

    LOGI(TAG, "FFDemux open file %s success", url);

    //读取文件信息
    ret = avformat_find_stream_info(ic, 0);

    if (ret != 0) {
        mux.unlock();
        char buf[1024] = {0};
        LOGI(TAG, "avformat_find_stream_info %s failed", url);
        av_strerror(ret, buf, sizeof(buf));
        return false;
    }

    this->totalMs = ic->duration / (AV_TIME_BASE / 1000);

    mux.unlock();
    LOGI(TAG, "totalMs  == %d ", totalMs);

    //获取音视频流下标
    getVPara();
    getAPara();

    return true;
}

XParameter FFDemux::getVPara() {

    mux.lock();
    if (!ic) {
        mux.unlock();
        LOGI(TAG, "AVFormatContext == null");
        return XParameter();
    }

    //获取视频流
    int index = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (index < 0) {
        mux.unlock();
        LOGI(TAG, "av_find_best_stream failed");
        return XParameter();
    }

    videoStream = index;
    LOGI(TAG, "视频流下标：：%d", index);
    XParameter para;
    para.para = ic->streams[index]->codecpar;
    mux.unlock();
    return para;
}


XParameter FFDemux::getAPara() {

    mux.lock();
    if (!ic) {
        mux.unlock();
        LOGI(TAG, "AVFormatContext == null");
        return XParameter();
    }

    //获取视频流
    int index = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (index < 0) {
        mux.unlock();
        LOGI(TAG, "av_find_best_stream failed");
        return XParameter();
    }

    audioStream = index;
    LOGI(TAG, "音频流下标：：%d", index);
    XParameter para;
    para.para = ic->streams[index]->codecpar;
    para.channels = ic->streams[index]->codecpar->channels;
    para.sample_rate = ic->streams[index]->codecpar->sample_rate;
    mux.unlock();
    return para;

}

//av_read_frame();
XData FFDemux::read() {
    mux.lock();
    if (!ic) {
        mux.unlock();
        return XData();
    }

    XData d;
    AVPacket *pkt = av_packet_alloc();
    int ret = av_read_frame(ic, pkt);

    //LOGI(TAG, "av_read_frame code == %d", ret);
    if (ret != 0) {
        av_packet_free(&pkt);
        return XData();
    }

    //LOGI(TAG, "pack size is %d ptss %lld", pkt->size, pkt->pts);

    d.data = (unsigned char *) pkt;
    d.size = pkt->size;

    if (pkt->stream_index == audioStream) {
        d.isAudio = true;
    } else if (pkt->stream_index == videoStream) {
        d.isAudio = true;
    } else {
        av_packet_free(&pkt);
        mux.unlock();
        return XData();
    }

    //转换pts
    pkt->pts = pkt->pts * (1000 * r2q(ic->streams[pkt->stream_index]->time_base));
    pkt->dts = pkt->dts * (1000 * r2q(ic->streams[pkt->stream_index]->time_base));
    d.pts = (int) pkt->pts;

    mux.unlock();
    return d;
}

FFDemux::FFDemux() {

    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;

        //注册所有封装器
        av_register_all();

        //注册所有的解码器
        avcodec_register_all();

        //初始化网络，否则无法解码在线资源
        avformat_network_init();
        LOGI(TAG, "register success");
    }
}


