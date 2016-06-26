package org.kaj.plugins.share;

import android.content.Intent;
import android.net.Uri;

import java.io.File;
import java.util.ArrayList;

import org.kaj.KajActivity;

public class Share {
	public static void ShareApp(){
		try{
		    ArrayList<Uri> uris = new ArrayList<Uri>();
		    Intent sendIntent = new Intent(Intent.ACTION_SEND_MULTIPLE);
		    sendIntent.setType("application/vnd.android.package-archive");
		    uris.add(Uri.fromFile(new File(KajActivity.getInstance().getApplicationInfo().publicSourceDir)));
		    sendIntent.putParcelableArrayListExtra(Intent.EXTRA_STREAM, uris);
		    KajActivity.getInstance().startActivity(Intent.createChooser(sendIntent, null));
		}catch(Exception e){
			e.printStackTrace();
		    ArrayList<Uri> uris = new ArrayList<Uri>();
		    Intent sendIntent = new Intent(Intent.ACTION_SEND_MULTIPLE);
		    sendIntent.setType("application/zip");
		    uris.add(Uri.fromFile(new File(KajActivity.getInstance().getApplicationInfo().publicSourceDir)));
		    sendIntent.putParcelableArrayListExtra(Intent.EXTRA_STREAM, uris);
		    KajActivity.getInstance().startActivity(Intent.createChooser(sendIntent, null));
		}
	}
}
