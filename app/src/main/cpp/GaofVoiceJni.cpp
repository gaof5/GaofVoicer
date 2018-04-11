#include <jni.h>
#include <string>
#include <fmod.hpp>
#include <unistd.h>
#include <android/log.h>

#define TAG "myDemo-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型
#undef com_gaof_gaofvoicer_VoicerFixer_MODE_NORMAL
#define com_gaof_gaofvoicer_VoicerFixer_MODE_NORMA 0
#undef com_gaof_gaofvoicer_VoicerFixer_MODE_LUOLI
#define com_gaof_gaofvoicer_VoicerFixer_MODE_LUOLI 1
#undef com_gaof_gaofvoicer_VoicerFixer_MODE_DASHU
#define com_gaof_gaofvoicer_VoicerFixer_MODE_DASHU 2
#undef com_gaof_gaofvoicer_VoicerFixer_MODE_JINGSONG
#define com_gaof_gaofvoicer_VoicerFixer_MODE_JINGSONG 3
#undef com_gaof_gaofvoicer_VoicerFixer_MODE_GAOGUAI
#define com_gaof_gaofvoicer_VoicerFixer_MODE_GAOGUAI 4
#undef com_gaof_gaofvoicer_VoicerFixer_MODE_KONGLING
#define com_gaof_gaofvoicer_VoicerFixer_MODE_KONGLING 5

bool isPlaying;
using namespace FMOD;
extern "C" {
    //JNIEXPORT jstring
    //JNICALL
    jstring Java_com_gaof_gaofvoicer_MainActivity_stringFromJNI(
            JNIEnv *env,
            jobject /* this */) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
    }
    void
    Java_com_gaof_gaofvoicer_VoicerFixer_fix(JNIEnv *env, jobject instance, jstring path_, jint mode) {
        const char *path = env->GetStringUTFChars(path_, 0);
        LOGE("进入方法");
        System *system;
        Sound *sound;
        Channel *channel;
        DSP *dsp;
        float frequency;
        //初始化
        System_Create(&system);
        //创建声音
    //    int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata
        system->init(32, FMOD_INIT_NORMAL, NULL);
        system->createSound(path, FMOD_DEFAULT, 0, &sound);
        LOGE("创建声音,mode=%d", mode);
        switch (mode) {
            case com_gaof_gaofvoicer_VoicerFixer_MODE_NORMA:
    //            (Sound *sound, ChannelGroup *channelgroup, bool paused, Channel **channel)
                system->playSound(sound, 0, false, &channel);
                LOGE("播放声音");
                break;
            case com_gaof_gaofvoicer_VoicerFixer_MODE_LUOLI:
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //2.0代表调高一个八度(12345671) 升高音调
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.0);
                //播放
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                LOGE("播放声音 升高音调");
                break;
            case com_gaof_gaofvoicer_VoicerFixer_MODE_DASHU:
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //降低音调
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.5);
                //播放
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case com_gaof_gaofvoicer_VoicerFixer_MODE_GAOGUAI:
                system->createDSPByType(FMOD_DSP_TYPE_NORMALIZE, &dsp);
                //播放
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                channel->getFrequency(&frequency);
                frequency = frequency * 1.6;
                channel->setFrequency(frequency);
                break;
            case com_gaof_gaofvoicer_VoicerFixer_MODE_KONGLING:
                //播放
                system->playSound(sound, 0, false, &channel);
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
                channel->addDSP(0, dsp);
                break;
            case com_gaof_gaofvoicer_VoicerFixer_MODE_JINGSONG:
                // FMOD_DSP_TYPE_TREMOLO 颤抖
                LOGI("%s", "惊悚");
                // 设置颤抖
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                // 设置颤抖的频率
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.8);
                system->playSound(sound, NULL, false, &channel);
                channel->addDSP(0, dsp);
                channel->getFrequency(&frequency);
                frequency = frequency * 0.7;
                channel->setFrequency(frequency);
                break;
            default:
                break;
        }

        system->update();
        bool isPlaying = true;
        // 需要等待，等声音全部播放完成
        // 检查是否播放完成
        while (isPlaying) {
            channel->isPlaying(&isPlaying);
            usleep(1000);
        }

        system->close();
        system->release();
        env->ReleaseStringUTFChars(path_, path);
    }

    void Java_com_gaof_gaofvoicer_VoicerFixer_stop(JNIEnv *env, jclass type, jstring path_) {
        LOGE("播放声音 stop");
        const char *path = env->GetStringUTFChars(path_, 0);
        env->ReleaseStringUTFChars(path_, path);
    }
}
