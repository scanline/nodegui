#pragma once

#include <QAudio>
#include <QMediaObject>
#include <QMediaPlayer>

#include "QtMultimedia/QMediaObject/qmediaobject_macro.h"
#include "core/Events/eventwidget.h"
#include "core/Events/eventwidget_macro.h"
class DLL_EXPORT NMediaPlayer : public QMediaPlayer, public EventWidget {
 public:
  Q_OBJECT
  EVENTWIDGET_IMPLEMENTATIONS(QMediaPlayer)
 public:
  using QMediaPlayer::QMediaPlayer;  // inherit all constructors of QMediaPlayer

  void connectSignalsToEventEmitter() {
    QMEDIAOBJECT_SIGNALS_ON_TARGET(this)
    QOBJECT_SIGNALS
    QObject::connect(this, &QMediaPlayer::audioAvailableChanged,
                     [=](bool available) {
                       Napi::Env env = this->emitOnNode.Env();
                       Napi::HandleScope scope(env);
                       this->emitOnNode.Call(
                           {Napi::String::New(env, "audioAvailableChanged"),
                            Napi::Boolean::New(env, available)});
                     });

    QObject::connect(
        this, &QMediaPlayer::audioRoleChanged, [=](QAudio::Role role) {
          Napi::Env env = this->emitOnNode.Env();
          Napi::HandleScope scope(env);
          this->emitOnNode.Call({Napi::String::New(env, "audioRoleChanged"),
                                 Napi::Boolean::New(env, role)});
        });

    QObject::connect(this, &QMediaPlayer::positionChanged, [=](int position) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "positionChanged"),
                             Napi::Number::New(env, position)});
    });

    QObject::connect(
        this, &QMediaPlayer::bufferStatusChanged, [=](int percentFilled) {
          Napi::Env env = this->emitOnNode.Env();
          Napi::HandleScope scope(env);
          this->emitOnNode.Call({Napi::String::New(env, "bufferStatusChanged"),
                                 Napi::Number::New(env, percentFilled)});
        });

    QObject::connect(this,
                     QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
                     [=](QMediaPlayer::Error error) {
                       Napi::Env env = this->emitOnNode.Env();
                       Napi::HandleScope scope(env);
                       this->emitOnNode.Call(
                           {Napi::String::New(env, "error"),
                            Napi::Number::New(env, static_cast<int>(error))});
                     });

    QObject::connect(this, &QMediaPlayer::stateChanged,
                     [=](QMediaPlayer::State state) {
                       Napi::Env env = this->emitOnNode.Env();
                       Napi::HandleScope scope(env);
                       this->emitOnNode.Call(
                           {Napi::String::New(env, "stateChanged"),
                            Napi::Number::New(env, static_cast<int>(state))});
                     });

    QObject::connect(this, &QMediaPlayer::mediaStatusChanged,
                     [=](QMediaPlayer::MediaStatus status) {
                       Napi::Env env = this->emitOnNode.Env();
                       Napi::HandleScope scope(env);
                       this->emitOnNode.Call(
                           {Napi::String::New(env, "mediaStatusChanged"),
                            Napi::Number::New(env, static_cast<int>(status))});
                     });

    QObject::connect(this, &QMediaPlayer::videoAvailableChanged,
                     [=](bool available) {
                       Napi::Env env = this->emitOnNode.Env();
                       Napi::HandleScope scope(env);
                       this->emitOnNode.Call(
                           {Napi::String::New(env, "videoAvailableChanged"),
                            Napi::Boolean::New(env, available)});
                     });

    QObject::connect(this, &QMediaPlayer::volumeChanged, [=](int volume) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "volumeChanged"),
                             Napi::Number::New(env, volume)});
    });
    
    QObject::connect(this, &QMediaPlayer::playbackRateChanged, [=](qreal rate) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "playbackRateChanged"),
                             Napi::Number::New(env, rate)});
    });    

    QObject::connect(this, &QMediaPlayer::seekableChanged, [=](bool seekable) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "seekableChanged"),
                             Napi::Boolean::New(env, seekable)});
    });

    QObject::connect(this, &QMediaPlayer::mutedChanged, [=](bool muted) {
      Napi::Env env = this->emitOnNode.Env();
      Napi::HandleScope scope(env);
      this->emitOnNode.Call({Napi::String::New(env, "mutedChanged"),
                             Napi::Boolean::New(env, muted)});
    });
  }
};