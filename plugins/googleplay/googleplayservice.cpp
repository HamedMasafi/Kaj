#ifdef QT_ANDROIDEXTRAS_LIB
#   include <QtAndroidExtras>
#endif

#include <QtQml>

#include "googleplayservice.h"

const int32_t MIN_PLAYERS = 1;
const int32_t MAX_PLAYERS = 3;

KAJ_DECL_SINGLETON(GooglePlayService)

GooglePlayService::GooglePlayService(QObject *parent) : KajPluginBase(parent)
{
    setInstacne(this);
}

void GooglePlayService::init()
{
    qmlRegisterType<GooglePlayService>(KAJ_QML_URI, 1, 0, QT_STRINGIFY(GooglePlayService));
}

void GooglePlayService::initGooglePlayGameServices()
{

#ifdef QT_ANDROIDEXTRAS_LIB
    qDebug() << "Connecting to google play service";
    QAndroidJniObject::callStaticMethod<void>(KAJ_JAVA_CLASS_NAME(googleplayservice, GooglePlayService),
                                              "Connect");
#else
//    Q_UNUSED(name)
#endif

#ifdef Q_OS_ANDROID
//    QtAndroid::androidActivity().callMethod<void>("loginGPGS");
#endif

#ifdef Q_OS_ANDROID1
    if (service_ != nullptr) {
        return;
    }

    gpg::AndroidInitialization::android_main(app_);

    // Game Services have not been initialized, create a new Game Services.
    gpg::AndroidPlatformConfiguration platform_configuration;
    platform_configuration.SetActivity(
//                app_->activity->clazz
            QtAndroid::androidActivity().object<jclass>()
    );
    gpg::GameServices::Builder builder;
    service_ =
            builder.SetOnAuthActionStarted([this](gpg::AuthOperation op) {
            // This callback is invoked when auth
            // action started
            // While auth action is going on, disable
            // auth and related UI
            OnAuthActionStarted(op);
})
            .SetOnAuthActionFinished([this](gpg::AuthOperation op,
                                     gpg::AuthStatus status) {
        // This callback is invoked when auth action finished
        // Check status code and update UI to signed-in state
        OnAuthActionFinished(op, status);
    })
//    .SetOnMultiplayerInvitationEvent([this](
//                                     gpg::MultiplayerEvent event, std::string match_id,
//                                     gpg::MultiplayerInvitation invitation) {
//        // Invoked when invitation has been received
//        // It can be received from the Play Game app, a notification, or
//        // live while the app is running.
//        // (e.g. Though PlayGam app, while the app is running)
//        //TODO: LOGI("MultiplayerInvitationEvent callback");

//        if (event ==
//                gpg::TurnBasedMultiplayerEvent::UPDATED_FROM_APP_LAUNCH) {

//            // In this case, an invitation has been accepted already
//            // in notification or in Play game app
////            gpg::RealTimeMultiplayerManager::RealTimeRoomResponse result =
////                    service_->RealTimeMultiplayer().AcceptInvitationBlocking(invitation, this);
////            if (gpg::IsSuccess(result.status)) {
////                room_ = result.room;
////                service_->RealTimeMultiplayer().ShowWaitingRoomUI(
////                            room_, MIN_PLAYERS,
////                            [this](gpg::RealTimeMultiplayerManager::
////                            WaitingRoomUIResponse const &waitResult) {
//////                    EnableUI(true);
////                    if (gpg::IsSuccess(waitResult.status)) {
////                        PlayGame();
////                    }
////                });
////            } else {
////                LeaveGame();
////            }
//        } else {
//            // Otherwise, show default inbox and let players to accept an
//            // invitation
////            ShowRoomInbox();
//        }
//    })
    .Create(platform_configuration);
#endif
}

#ifdef Q_OS_ANDROID
void GooglePlayService::OnAuthActionStarted(gpg::AuthOperation op)
{

}

void GooglePlayService::OnAuthActionFinished(gpg::AuthOperation op, gpg::AuthStatus status)
{

}

void GooglePlayService::PlayGame()
{

}

void GooglePlayService::LeaveGame()
{

}
#endif
