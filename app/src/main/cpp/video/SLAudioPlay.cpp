//
// Created by wjw on 2019-11-03.
//

#include "SLAudioPlay.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "LogUtils.h"
#include "native-lib.h"

static SLObjectItf engineSL = nullptr;
static SLEngineItf eng = nullptr;
static SLObjectItf mix = nullptr;
static SLObjectItf player = nullptr;
static SLPlayItf iplayer = nullptr;
static SLAndroidSimpleBufferQueueItf pcmQue = nullptr;

SLAudioPlay::SLAudioPlay() {
    buf = new unsigned char[1024 * 1024];
}

SLAudioPlay::~SLAudioPlay() {
    delete buf;
    buf = nullptr;
}

static SLEngineItf createSL() {
    SLresult re;
    SLEngineItf en;
    re = slCreateEngine(&engineSL, 0, nullptr, 0, nullptr, nullptr);
    if (re != SL_RESULT_SUCCESS) {
        return nullptr;
    }

    re = (*engineSL)->Realize(engineSL, SL_BOOLEAN_FALSE);
    if (re != SL_RESULT_SUCCESS) {
        return nullptr;
    }

    re = (*engineSL)->GetInterface(engineSL, SL_IID_ENGINE, &en);
    if (re != SL_RESULT_SUCCESS) {
        return nullptr;
    }

    return en;
}

void SLAudioPlay::playCall(void *bufq) {
    if (!bufq) {
        return;
    }

    SLAndroidSimpleBufferQueueItf bf = (SLAndroidSimpleBufferQueueItf) bufq;

    //阻塞
    XData d = getData();

    if (d.size <= 0) {
        LOGE(TAG, "getData() size is 0");
        return;
    }

    if (!buf) {
        return;
    }

    memcpy(buf, d.data, d.size);
    mux.lock();
    (*bf)->Enqueue(bf, buf, d.size);
    mux.unlock();
    d.Drop();
}

static void pcmCall(SLAndroidSimpleBufferQueueItf bf, void *context) {
    SLAudioPlay *ap = (SLAudioPlay *) context;
    if (!ap) {
        LOGE(TAG, "pcmCall failed context is null");
        return;
    }
    ap->playCall((void *) bf);
}

void SLAudioPlay::close() {

    mux.lock();

    //停止播放
    if (iplayer && (*iplayer)) {
        (*iplayer)->SetPlayState(iplayer, SL_PLAYSTATE_STOPPED);
    }

    //清理播放队列
    if (pcmQue && (*pcmQue)) {
        (*pcmQue)->Clear(pcmQue);
    }

    //销毁player对象
    if (player && (*player)) {
        (*player)->Destroy(player);
    }

    //销毁混音器
    if (mix && (*mix)) {
        (*mix)->Destroy(mix);
    }

    //销毁播放引擎
    if (engineSL && (*engineSL)) {
        (*engineSL)->Destroy(engineSL);
    }
    mux.unlock();
}


bool SLAudioPlay::startPlay(XParameter out) {

    close();
    mux.lock();

    //1 创建引擎
    eng = createSL();

    if (eng) {
        LOGE(TAG, "createSL success");
    } else {
        mux.unlock();
        LOGE(TAG, "createSL failed");
        return false;
    }

    //2 创建混音器
    SLresult re = 0;
    re = (*eng)->CreateOutputMix(eng, &mix, 0, nullptr, nullptr);

    if (re != SL_RESULT_SUCCESS) {
        mux.unlock();
        LOGE(TAG, "SL_RESULT_SUCCESS failed");
        return false;
    }

    re = (*mix)->Realize(mix, SL_BOOLEAN_FALSE);

    if (re != SL_RESULT_SUCCESS) {
        mux.unlock();
        LOGE(TAG, "(*mix)->Realize  failed");
        return false;
    }

    SLDataLocator_OutputMix outmix = {SL_DATALOCATOR_OUTPUTMIX, mix};
    SLDataSink audioSink = {&outmix, nullptr};

    //3 配置音频信息
    //缓冲队列
    SLDataLocator_AndroidBufferQueue que = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 10};

    //音频格式
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            (SLuint32) out.channels,//声道数
            (SLuint32) out.sample_rate * 1000,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN //字节序，小端
    };

    SLDataSource ds = {&que, &pcm};

    //4 创建播放器
    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE};
    const SLboolean req[] = {SL_BOOLEAN_TRUE};

    re = (*eng)->CreateAudioPlayer(eng, &player, &ds, &audioSink,
                                   sizeof(ids) / sizeof(SLInterfaceID), ids, req);

    if (re != SL_RESULT_SUCCESS) {
        mux.unlock();
        LOGE(TAG, "CreateAudioPlayer failed");
        return false;
    } else {
        LOGE(TAG, "CreateAudioPlayer success");
    }

    (*player)->Realize(player, SL_BOOLEAN_FALSE);

    //获取player接口
    re = (*player)->GetInterface(player, SL_IID_PLAY, &iplayer);
    if (re != SL_RESULT_SUCCESS) {
        mux.unlock();
        LOGE(TAG, "GetInterface SL_IID_PLAY  failed");
        return false;
    }

    re = (*player)->GetInterface(player, SL_IID_BUFFERQUEUE, &pcmQue);
    if (re != SL_RESULT_SUCCESS) {
        mux.unlock();
        LOGE(TAG, "GetInterface SL_IID_BUFFERQUEUE failed");
        return false;
    }

    //设置回调函数，播放队列空调用
    (*pcmQue)->RegisterCallback(pcmQue, pcmCall, this);

    //设置为播放状态
    (*iplayer)->SetPlayState(iplayer, SL_PLAYSTATE_PLAYING);

    //启动队列回调
    (*pcmQue)->Enqueue(pcmQue, "", 1);

    mux.unlock();
    LOGE(TAG, "SLAudioPlay::startPlay success");

    return true;
}






