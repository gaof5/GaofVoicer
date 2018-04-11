package com.gaof.gaofvoicer;

public class VoicerFixer {

    public static final int MODE_NORMAL=0;
    public static final int MODE_LUOLI=1;
    public static final int MODE_DASHU=2;
    public static final int MODE_JINGSONG=3;
    public static final int MODE_GAOGUAI=4;
    public static final int MODE_KONGLING=5;

    static {
        System.loadLibrary("GaofVoiceJni");
    }

    public static native void fix(String path,int mode);

    public static native void stop(String path);

}
