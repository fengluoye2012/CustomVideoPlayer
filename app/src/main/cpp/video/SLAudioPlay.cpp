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

SLAudioPlay::SLAudioPlay() {
    buf = new unsigned char[1024 * 1024];

}

SLAudioPlay::~SLAudioPlay() {
    delete buf;
    buf = nullptr;
}


bool SLAudioPlay::startPlay(XParameter out) {

    //1 创建引擎
    eng = createSL();

    if (eng) {
        LOGE(TAG, "createSL success");
    } else {
        LOGE(TAG, "createSL failed");
        return false;
    }

    //2 创建混音器
    SLresult re = 0;
    re = (*eng)->CreateOutputMix(eng, &mix, 0, nullptr, nullptr);

    if (re != SL_RESULT_SUCCESS) {
        LOGE(TAG, "SL_RESULT_SUCCESS failed");
        return false;
    }

    re = (*mix)->Realize(mix, SL_BOOLEAN_FALSE);

    if (re != SL_RESULT_SUCCESS) {
        LOGE(TAG, "(*mix)->Realize  failed");
        return false;
    }

    SLDataLocator_OutputMix outmix = {SL_DATALOCATOR_OUTPUTMIX, mix};
    SLDataSink audioSink = {&outmix, 0};

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


    return false;
}

void SLAudioPlay::playCall(void *bufq) {


}


