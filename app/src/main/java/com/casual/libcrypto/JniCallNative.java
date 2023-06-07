package com.casual.libcrypto;

public class JniCallNative {
    static {
        System.loadLibrary("crypto-utils");
    }
    public static native String Encrypt(String plaintext);
    public static native String Decrypt(String plaintext);
}
