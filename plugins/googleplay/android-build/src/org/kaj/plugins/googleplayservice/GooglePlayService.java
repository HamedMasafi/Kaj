package org.kaj.plugins.googleplayservice;

import android.os.Bundle;

import org.kaj.KajActivity;

import com.google.android.gms.common.ConnectionResult;
//import com.google.example.games.basegameutils.BaseGameUtils;
//import com.google.example.games.basegameutils.GameHelper;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.GoogleApiClient.ConnectionCallbacks;
import com.google.android.gms.common.api.GoogleApiClient.OnConnectionFailedListener;
import com.google.android.gms.plus.Plus;

public class GooglePlayService {
	public GooglePlayService(){
		//gameHelper = new GameHelper(this, GameHelper.CLIENT_ALL);
	    
	    
	}

	private static GoogleApiClient myClient = null;
	
	public static void Connect(){
		initGPG();
		myClient.connect();
	}
	private static void initGPG(){
		ConnectionCallbacks callBacks = new ConnectionCallbacks() {
			@Override
			public void onConnectionSuspended(int arg0) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onConnected(Bundle arg0) {
				// TODO Auto-generated method stub
				
			}
		};
		OnConnectionFailedListener failListener = new OnConnectionFailedListener() {
			
			@Override
			public void onConnectionFailed(ConnectionResult arg0) {
				// TODO Auto-generated method stub
				
			}
		};
		int resultCode = GooglePlayServicesUtil.isGooglePlayServicesAvailable(KajActivity.getInstance());
		
		myClient = new GoogleApiClient.Builder(KajActivity.getInstance())
		    .addApi(Plus.API)
		    .addScope(Plus.SCOPE_PLUS_PROFILE)
		    .addConnectionCallbacks(callBacks)
		    .addOnConnectionFailedListener(failListener)
		    .build();
	}

}
