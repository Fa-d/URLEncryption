package com.faddy.libcrypto

import android.annotation.SuppressLint
import android.util.Base64
import java.nio.charset.Charset
import javax.crypto.Cipher
import javax.crypto.spec.IvParameterSpec
import javax.crypto.spec.SecretKeySpec

object CryptoUtils {
    private const val TRANSFORMATION = "AES"
    private const val SECRET_KEY = "e81wolan12dfw31f"
    fun encrypt(data: String): String? {
        return try {
            val secretKeySpec = SecretKeySpec(SECRET_KEY.toByteArray(), TRANSFORMATION)
            @SuppressLint("GetInstance") val cipher = Cipher.getInstance(TRANSFORMATION)
            cipher.init(
                Cipher.ENCRYPT_MODE,
                secretKeySpec,
                IvParameterSpec(ByteArray(cipher.getBlockSize()))
            )
            val bytesToDecrypt = cipher.doFinal(data.toByteArray())
            Base64.encodeToString(bytesToDecrypt, Base64.DEFAULT)
        } catch (e: Exception) {
            null
        }
    }

    fun decrypt(data: String): String? {
        return try {
            val secretKeySpec = SecretKeySpec(SECRET_KEY.toByteArray(), TRANSFORMATION)
            @SuppressLint("GetInstance") val cipher = Cipher.getInstance(TRANSFORMATION)
            val encryptedContent = Base64.decode(data.toByteArray(), Base64.DEFAULT)
            cipher.init(
                Cipher.DECRYPT_MODE,
                secretKeySpec,
                IvParameterSpec(ByteArray(cipher.getBlockSize()))
            )
            val original = cipher.doFinal(encryptedContent)
            String(original, Charset.forName("UTF-8"))
        } catch (e: Exception) {
            null
        }
    }
}
