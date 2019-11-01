//
// Created by wjw on 2019-10-31.
//

#include "FFDemux.h"
#include "LogUtils.h"

extern "C" {
#include "libavformat/avformat.h"
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
    }
}

bool FFDemux::open(const char *url) {

    LOGI(TAG, "open file %s begin", url);
    int ret = avformat_open_input(&ic, url, nullptr, nullptr);

    if (ret != 0) {
        char buf[1024] = {0};
        LOGI(TAG, "open file %s failed", url);
        av_strerror(ret, buf, sizeof(buf));
        return false;
    }

    LOGI(TAG, "open file %s success", url);

    //读取文件信息
    ret = avformat_find_stream_info(ic, nullptr);

    if (ret != 0) {
        char buf[1024] = {0};
        LOGI(TAG, "avformat_find_stream_info %s failed", url);
        av_strerror(ret, buf, sizeof(buf));
        return false;
    }

    this->totalMs = static_cast<int>(ic->duration / (AV_TIME_BASE / 1000));

    LOGI(TAG, "totalMs  == %d ", totalMs);

    //获取音视频流下标，并且
    getVPara();
    getAPara();

    return true;
}

XParameter FFDemux::getVPara() {
    if (!ic) {
        return XParameter();
    }

    //获取视频流
    int index = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (index < 0) {
        LOGI(TAG, "av_find_best_stream failed");
        return XParameter();
    }

    videoStream = index;
    LOGI(TAG, "视频流下标：：%d", videoStream);
    XParameter para;
    para.para = ic->streams[videoStream]->codecpar;
    return para;
}


XParameter FFDemux::getAPara() {

    if (!ic) {
        return XParameter();
    }

    //获取视频流
    int index = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (index < 0) {
        LOGI(TAG, "av_find_best_stream failed");
        return XParameter();
    }

    audioStream = index;
    LOGI(TAG, "音频流下标：：%d", audioStream);
    XParameter para;
    para.para = ic->streams[audioStream]->codecpar;
    return para;

}


Data FFDemux::read() {
    if (!ic) {
        return Data();
    }

    Data d;
    AVPacket *pkt = av_packet_alloc();
    int ret = av_read_frame(ic, pkt);

    if (ret != 0) {
        av_packet_free(&pkt);
        return Data();
    }

    d.data = reinterpret_cast<unsigned char *>(pkt);
    d.size = pkt->size;

    if (pkt->stream_index == audioStream) {
        d.isAudio = true;
    } else if (pkt->stream_index == videoStream) {
        d.isAudio = true;
    } else {
        av_packet_free(&pkt);
        return Data();
    }

    return d;
}
