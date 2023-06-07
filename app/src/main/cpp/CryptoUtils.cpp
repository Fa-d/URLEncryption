//
// Created by pengfei.guo on 2021/12/8.
//

#include <iostream>
#include "AES.h"
#include "Base64.h"
#include "CryptoUtils.h"

#include <jni.h>
#include <string>

using namespace std;

const char g_key[] = "ip6qN00KnbJaoOoQ";
const char g_iv[17] = "x1bouh233ci0sp6u";//CBC MODE不需要关心chain，可以填空
string Encrypt(const string &strSrc) //AES加密
{
    size_t length = strSrc.length();
    int block_num = length / BLOCK_SIZE + 1;
    //明文
    char *szDataIn = new char[block_num * BLOCK_SIZE + 1];
    memset(szDataIn, 0x00, block_num * BLOCK_SIZE + 1);
    strcpy(szDataIn, strSrc.c_str());

    //进行PKCS7Padding填充。
    int k = length % BLOCK_SIZE;
    int j = length / BLOCK_SIZE;
    int padding = BLOCK_SIZE - k;
    for (int i = 0; i < padding; i++)
    {
        szDataIn[j * BLOCK_SIZE + k + i] = padding;
    }
    szDataIn[block_num * BLOCK_SIZE] = '\0';

    //加密后的密文
    char *szDataOut = new char[block_num * BLOCK_SIZE + 1];
    memset(szDataOut, 0, block_num * BLOCK_SIZE + 1);

    //进行进行AES的ECB模式加密
    AES aes;
    aes.MakeKey(g_key, g_iv, 16, 16);
    aes.Encrypt(szDataIn, szDataOut, block_num * BLOCK_SIZE, AES::CBC);
    string str = base64_encode((unsigned char*) szDataOut,
            block_num * BLOCK_SIZE);
    delete[] szDataIn;
    delete[] szDataOut;
    return str;
}
string Decrypt(const string& strSrc) //AES解密
{
    string strData = base64_decode(strSrc);
    size_t length = strData.length();
    //密文
    char *szDataIn = new char[length + 1];
    memcpy(szDataIn, strData.c_str(), length+1);
    //明文
    char *szDataOut = new char[length + 1];
    memcpy(szDataOut, strData.c_str(), length+1);

    //进行AES的CBC模式解密
    AES aes;
    aes.MakeKey(g_key, g_iv, 16, 16);
    aes.Decrypt(szDataIn, szDataOut, length, AES::CBC);

    //去PKCS7Padding填充
    if (0x00 < szDataOut[length - 1] <= 0x16)
    {
        int tmp = szDataOut[length - 1];
        for (int i = length - 1; i >= length - tmp; i--)
        {
            if (szDataOut[i] != tmp)
            {
                memset(szDataOut, 0, length);
                cout << "去填充失败！解密出错！！" << endl;
                break;
            }
            else
                szDataOut[i] = 0;
        }
    }
    string strDest(szDataOut);
    delete[] szDataIn;
    delete[] szDataOut;
    return strDest;
}
//extern "C"
//JNIEXPORT jstring JNICALL
//Java_com_math3_libsqlite_MainActivity_Encrypt(JNIEnv *env, jobject thiz, jstring plaintext) {
//    // TODO: implement Encrypt()
//    const char* chars = env->GetStringUTFChars(plaintext, 0);
//    std::string str = std::string(chars);
//    std::string text = EncryptionAES(str);
//    env->ReleaseStringUTFChars(plaintext, chars);
//    return env->NewStringUTF(text.c_str());
//}
//extern "C"
//JNIEXPORT jstring JNICALL
//Java_com_math3_libsqlite_MainActivity_Dencrypt(JNIEnv *env, jobject thiz, jstring plaintext) {
//    // TODO: implement Dencrypt()
//    const char* chars = env->GetStringUTFChars(plaintext, 0);
//    std::string str = std::string(chars);
//    std::string text = DecryptionAES(str);
//    env->ReleaseStringUTFChars(plaintext, chars);
//    return env->NewStringUTF(text.c_str());
//}