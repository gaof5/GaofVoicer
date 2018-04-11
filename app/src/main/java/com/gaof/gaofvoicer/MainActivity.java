package com.gaof.gaofvoicer;

import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import org.fmod.FMOD;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("GaofVoiceJni");
    }

    //        String path= Environment.getExternalStorageDirectory().getAbsolutePath()+"/xiangsui.mp3";
    //替换成自己的音频文件路径
    String path= Environment.getExternalStorageDirectory().getAbsolutePath()+"/xiangxi.m4a";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.M){
            String[] perms={"android.permission.RECORD_AUDIO","android.permission.WRITE_EXTERNAL_STORAGE"};
            if(checkSelfPermission(perms[0])== PackageManager.PERMISSION_DENIED||
                    checkSelfPermission(perms[1])==PackageManager.PERMISSION_DENIED){
                requestPermissions(perms,200);
            }
        }
        FMOD.init(this);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        FMOD.close();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public void fixVoice(View view) {
        Log.e("fixVoice","path="+path);
        switch (view.getId()){
            case R.id.btNormal:
                VoicerFixer.fix(path,VoicerFixer.MODE_NORMAL);
                break;
            case R.id.btLuoLi:
                VoicerFixer.fix(path,VoicerFixer.MODE_LUOLI);
                break;
            case R.id.btDaShu:
                VoicerFixer.fix(path,VoicerFixer.MODE_DASHU);
                break;
            case R.id.btGaoGuai:
                VoicerFixer.fix(path,VoicerFixer.MODE_GAOGUAI);
                break;
            case R.id.btKongLing:
                VoicerFixer.fix(path,VoicerFixer.MODE_KONGLING);
                break;
            case R.id.btJingSong:
                VoicerFixer.fix(path,VoicerFixer.MODE_JINGSONG);
                break;
            case R.id.btStop:
                VoicerFixer.stop(path);
//                VoicerFixer.fix(path,-1);
                break;
        }
    }
}
