//
// Created by zzh on 2018/9/27 0027.
//

#include <log.h>
#include <jni.h>
#include <mutex>
#include "Beauty.h"
#include <android/native_window_jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

using namespace std;

mutex gMutex;
Beauty *beauty = nullptr;

extern "C"
JNIEXPORT jint JNICALL
Java_cn_zzh_videoeditor_view_CameraView__1init(JNIEnv *env, jclass type, jobject surface,
                                                      jint width, jint height, jobject manager) {
    unique_lock<mutex> lock(gMutex);
    if (beauty) {
        beauty->stop();
        delete beauty;
    }
    beauty = new Beauty();
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    AAssetManager *assetManager = AAssetManager_fromJava(env, manager);
    int textureId = beauty->init(assetManager, window, width, height);

    return textureId;
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_zzh_videoeditor_view_CameraView__1draw(JNIEnv *env, jclass type, jfloatArray matrix_,
                                                      jfloat beautyLevel, jfloat saturate,
                                                      jfloat bright, jboolean recording) {
    unique_lock<mutex> lock(gMutex);
    if (!beauty) {
        LOGE("draw error, beauty is null");
        return;
    }
    jfloat *matrix = env->GetFloatArrayElements(matrix_, NULL);
    beauty->draw(matrix, beautyLevel, saturate, bright, recording);
    env->ReleaseFloatArrayElements(matrix_, matrix, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_zzh_videoeditor_view_CameraView__1stop(JNIEnv *env, jclass type) {
    unique_lock<mutex> lock(gMutex);
    if (beauty) {
        beauty->stop();
        delete beauty;
        beauty = nullptr;
    }
}


