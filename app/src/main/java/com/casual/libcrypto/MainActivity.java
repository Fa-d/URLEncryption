package com.casual.libcrypto;

import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;


public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.d("MainPlain", "oncreate");
        String enTxt = JniCallNative.Encrypt("this is test string!");
        Log.d("MainPlain", enTxt);
        String deTxt = JniCallNative.Decrypt(enTxt);
        Log.d("MainPlain", deTxt);

        EditText inputET = findViewById(R.id.input1);
        TextView encTV = findViewById(R.id.encRes);
        TextView decTV = findViewById(R.id.decRes);

        inputET.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {

            }

            @Override
            public void afterTextChanged(Editable s) {
                s.toString();
                String encData = JniCallNative.Encrypt(s.toString());
                String decData = JniCallNative.Decrypt(encData);
                encTV.setText(encData);
                decTV.setText(decData);
            }
        });

//        String enTxt01 = CryptoUtils.encrypt("this is test string!");
//        Log.d("MainPlain", enTxt);
        //  String deTxt01 = CryptoUtils.decrypt(enTxt);
        // Log.d("MainPlain", deTxt01);
    }
}