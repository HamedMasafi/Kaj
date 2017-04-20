package org.tooj;

import android.annotation.TargetApi;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
//import com.google.example.games.basegameutils.BaseGameUtils;
//import com.google.example.games.basegameutils.GameHelper;
import org.qtproject.qt5.android.bindings.QtActivity;

public class ToojActivity extends QtActivity{

	private static ToojActivity instance;
	private boolean _transparentStatusBar = false;
    private boolean _transparentNavigationBar = false;
    //private GameHelper gameHelper;
    
	public ToojActivity(){
		instance = this;
	//	        gameHelper = new GameHelper(this, GameHelper.CLIENT_ALL);
		Log.i("ToojActivity", "ctor");
	}
	
	@TargetApi(Build.VERSION_CODES.KITKAT)
	@Override
	public void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		Window w = getWindow();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            w.setFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION, WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);
            w.setFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS, WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
            _transparentStatusBar = true;
            _transparentNavigationBar = true;
        } else {
            w.setFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS, WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
            _transparentStatusBar = true;
        }
	}
	
	public static ToojActivity getInstance() {
        return ToojActivity.instance;
    }

    public void SetStatusBarIsTransparent(boolean value) {
        _transparentStatusBar = value;
    }

    public void GetNavigationBarIsTransparent(boolean value) {
        _transparentNavigationBar = value;
    }
    
    public boolean GetStatusBarIsTransparent() {
        return _transparentStatusBar;
    }

    public boolean GetNavigationBarIsTransparent() {
        return _transparentNavigationBar;
    }

	public void loginGPGS() {
        try {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    //gameHelper.beginUserInitiatedSignIn();
                }
            });
        } catch (Exception e) {
                e.printStackTrace();
        }
    }
}
