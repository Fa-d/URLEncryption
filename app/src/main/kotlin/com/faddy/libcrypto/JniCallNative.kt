package com.faddy.libcrypto

object JniCallNative {
    init {
        System.loadLibrary("blackbox")
    }

    external fun Encrypt(plaintext: String?): String?
    external fun Decrypt(plaintext: String?): String?
}
