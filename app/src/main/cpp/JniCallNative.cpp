//
// Created by pengfei.guo on 2021/12/9.
//

#include <jni.h>
#include <string>
#include "CryptoUtils.h"
extern "C"
JNIEXPORT jstring JNICALL Java_com_casual_libcrypto_JniCallNative_Encrypt
        (JNIEnv *env, jclass, jstring plaintext)
{
    const char* chars = env->GetStringUTFChars(plaintext, 0);
    std::string str = std::string(chars);
    std::string text = Encrypt(str);
    env->ReleaseStringUTFChars(plaintext, chars);
    return env->NewStringUTF(text.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL Java_com_casual_libcrypto_JniCallNative_Decrypt
        (JNIEnv *env, jclass, jstring plaintext)
{
    const char* chars = env->GetStringUTFChars(plaintext, 0);
    std::string str = std::string(chars);
    std::string text = Decrypt(str);
    env->ReleaseStringUTFChars(plaintext, chars);
    return env->NewStringUTF(text.c_str());
}