#ifndef GOOGLEPLAYSERVICE_H
#define GOOGLEPLAYSERVICE_H

#include <kajpluginbase.h>

#ifdef Q_OS_ANDROID
#include <jni.h>
#include <errno.h>
#include "gpg/gpg.h"
#include "gpg/achievement.h"
#include "gpg/achievement_manager.h"
#include "gpg/builder.h"
#include "gpg/debug.h"
#include "gpg/default_callbacks.h"
#include "gpg/game_services.h"
#include "gpg/leaderboard.h"
#include "gpg/leaderboard_manager.h"
#include "gpg/platform_configuration.h"
#include "gpg/player_manager.h"
#include "gpg/score_page.h"
#include "gpg/types.h"
#include <android/log.h>
#include "android/native_activity.h"
#include <android/native_window_jni.h>
#endif

class GooglePlayService : public KajPluginBase//, public gpg::IRealTimeEventListener
{
    Q_OBJECT
    KAJ_SINGLETON(GooglePlayService)

public:
    explicit GooglePlayService(QObject *parent = 0);
    static void init();

public slots:
    void initGooglePlayGameServices();

private:
#ifdef Q_OS_ANDROID
    void OnAuthActionStarted(gpg::AuthOperation op);
    void OnAuthActionFinished(gpg::AuthOperation op, gpg::AuthStatus status);
//    void OnRoomStatusChanged(RealTimeRoom const &room);
//    void OnConnectedSetChanged(gpg::RealTimeRoom const &room);
//    void OnP2PConnected(gpg::RealTimeRoom const &room, gpg::MultiplayerParticipant const &participant);
//    void OnP2PDisconnected(gpg::RealTimeRoom const &room, gpg::MultiplayerParticipant const &participant);
//    void OnParticipantStatusChanged(gpg::RealTimeRoom const &room, gpg::MultiplayerParticipant const &participant);
//    void OnDataReceived(RealTimeRoom const &room,
//                                  MultiplayerParticipant const &from_participant,
//                                  std::vector<uint8_t> data,
//                                  bool is_reliable);

    void PlayGame();
    void LeaveGame();


    std::unique_ptr<gpg::GameServices> service_;
    android_app *app_;
    gpg::RealTimeRoom room_;
#endif
};

KAJ_DECLARE_PLUGIN(GooglePlayService)

#endif // GOOGLEPLAYSERVICE_H
