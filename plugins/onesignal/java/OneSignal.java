package org.kaj.plugins;

import android.content.Intent;
import android.util.Log;

import org.kaj.KajApplication;
import com.onesignal.OSNotification;
import com.onesignal.OSNotificationOpenResult;
import com.tooska.geltaxi.TooskaActivity;

class NotificationReceivedHandler implements com.onesignal.OneSignal.NotificationReceivedHandler {
    @SuppressWarnings("JniMissingFunction")
    public native static void signalReceived(String title, String message);

    @Override
    public void notificationReceived(OSNotification osNotification) {
        signalReceived(osNotification.payload.title, osNotification.payload.body);
    }
}

class NotificationOpenedHandler implements com.onesignal.OneSignal.NotificationOpenedHandler {
    @SuppressWarnings("JniMissingFunction")
    public native static void signalOpened(String title, String message);

    @Override
    public void notificationOpened(OSNotificationOpenResult result) {
        if(OneSignal.OpenActivity){
            Intent intent = new Intent(KajApplication.getContext(), TooskaActivity.class);
            intent.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT | Intent.FLAG_ACTIVITY_NEW_TASK);
            KajApplication.getContext().startActivity(intent);
        }
        signalOpened(result.notification.payload.title, result.notification.payload.body);
    }
}

public class OneSignal{

    public static boolean OpenActivity;

    public static void Init(String applicationId){
        OpenActivity = false;

        com.onesignal.OneSignal.setInFocusDisplaying(com.onesignal.OneSignal.OSInFocusDisplayOption.Notification);
        com.onesignal.OneSignal.init(KajApplication.getContext(), "REMOTE", applicationId,
                new NotificationOpenedHandler(),
                new NotificationReceivedHandler());
        /*
        com.onesignal.OneSignal.startInit(KajApplication.getContext())
                .inFocusDisplaying(com.onesignal.OneSignal.OSInFocusDisplayOption.Notification)
                .setNotificationReceivedHandler(new NotificationReceivedHandler())
                .setNotificationOpenedHandler(new NotificationOpenedHandler())
                .unsubscribeWhenNotificationsAreDisabled(true)
                .init();
        */
    }
}
